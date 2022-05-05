package tools.communication;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;

import tools.communication.AbstractChannel;
import tools.communication.CommunicationConfig;
import tools.communication.Receiver;
import tools.communication.Sender;

/**
 * @author francoise.perrin -
 * Inspiration Jacques SARAYDARYAN, Adrien GUENARD -
 *
 * 
 */
public class ServerChannel extends AbstractChannel implements Runnable {
	private ServerSocket socServer;
	private Socket socClient;
	protected List<Sender> senderList;
	protected Receiver receiver;

	private Thread waitConnectionThread;

	public ServerChannel(CommunicationConfig config,
			BlockingQueue<Object> msgQueue) {
		super(config, msgQueue);
		senderList = new LinkedList<Sender>();
		waitConnectionThread = new Thread(this, "waitConnectionThread");
	}

	@Override
	public void openConnection() throws IOException {
		waitConnectionThread.start();
	}

	@Override
	public void closeChannel() throws IOException {
		try {
			waitConnectionThread.join(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		if (receiver != null)
			receiver.stop();
		for(Sender sender : senderList) {
			if (sender != null)
				sender.stop();
		}
		if (socClient != null)
			socClient.close();
		if (socServer != null)
			socServer.close();
	}

	/**
	 * Chaque fois qu'un ClientChannel, tente de se connecter au server
	 * une Socket client est crée (socServer.accept()),
	 * le Receiver et le Sender associés à la socket également,
	 * puis le sender est ajouté à la liste des senders
	 * afin que le server propage l'envoi de messages sur toutes 
	 * les Socket clientes
	 */
	@Override
	public void run() {

		try {
			int i=0;
			ObjectInputStream inputStream = null;
			ObjectOutputStream ouputStream = null;
			socServer = new ServerSocket(config.getPort());

			while (true) {

				System.out.println("accept client dans server " + i);
				socClient = socServer.accept();

				ouputStream= new ObjectOutputStream(socClient.getOutputStream());

				Sender sender = new Sender(ouputStream);
				senderList.add(sender);

				inputStream = new ObjectInputStream(socClient.getInputStream());
				receiver = new Receiver(inputStream, msgQueue);
				receiver.start();
				i++;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

	}


	/**
	 * @param message
	 * Propage les messages à tous les receiver des ClientChannel
	 */
	@Override
	public void writeMessage(Object message){
		try {
			for(Sender sender : senderList) {
				sender.write(message);
			}
		} catch (IOException e) {
			System.err.println("Erreur lors de l'ecriture de donn�es "+e.getMessage());
		}
	}

}

