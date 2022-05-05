package tools.communication;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.concurrent.BlockingQueue;

/**
 * @author francoise.perrin -
 * Inspiration Jacques SARAYDARYAN, Adrien GUENARD -
 *
 * 
 */
public class Receiver implements Runnable{
	private Thread thread;
	private ObjectInputStream inputStream;
	private boolean isEnd;
	private BlockingQueue<Object> msgQueue;

	public Receiver(ObjectInputStream inputStream,BlockingQueue<Object> msgQueue) {
		this.inputStream = inputStream;
		this.msgQueue = msgQueue;
		this.thread = new Thread(this,"ReceiverThread");
		this.isEnd = false;
	}

	public void start() {
		thread.start();
	}

	public void stop() {
		this.isEnd=true;
		try {
			this.thread.join(100);
			if (inputStream != null)
				try {
					inputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
		} catch (InterruptedException e) {
			System.err.println("Impossible d'arr�ter le thread de lecteur"+e.getMessage());
		}
	}

	@Override
	public void run() {
		while(!isEnd){
			try {
				Object message=this.inputStream.readObject();

				if(message!=null){
					msgQueue.put(message);
				}
			} catch (IOException e) {
				if(!isEnd){
					System.err.println("Erreur lors de la lecture receveur : "+e.getMessage());
				}
			} catch (InterruptedException e) {
				if(!isEnd){
					System.err.println("Erreur lors de la mise en queue"+e.getMessage());
				}
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
		}
	}

}
