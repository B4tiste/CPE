package tools.communication;



import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
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
public class ClientChannel extends AbstractChannel implements Runnable{

	private Thread waitConnectionThread;
	private Socket socClient;
	private Sender sender;
	private Receiver receiver;

	public ClientChannel(CommunicationConfig config,
			BlockingQueue<Object> msgQueue) {
		super(config, msgQueue);
		waitConnectionThread = new Thread(this, "waitConnectionThreadClient");
	}

	@Override
	public void openConnection() throws IOException {
		waitConnectionThread.start();
	}

	@Override
	public void closeChannel() throws IOException {
		
		if (receiver != null)
			receiver.stop();
		if (sender != null)
			sender.stop();
		if (socClient != null)
			socClient.close();
	}

	@Override
	public void run() {
		ObjectInputStream inputStream = null;
		ObjectOutputStream ouputStream = null;
		try {
			socClient = new Socket(config.getIp(), config.getPort());
			
			ouputStream= new ObjectOutputStream(socClient.getOutputStream());
			sender = new Sender(ouputStream);
			
			inputStream = new ObjectInputStream(socClient.getInputStream());
			receiver = new Receiver(inputStream,msgQueue);
			receiver.start();
			
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public void writeMessage(Object message){
		try {
			this.sender.write(message);
			
		} catch (IOException e) {
			System.err.println("Erreur lors de l'ecriture de donn�es "+e.getMessage());
		}
	}
}

