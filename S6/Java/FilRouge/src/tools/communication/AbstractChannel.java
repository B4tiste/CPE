package tools.communication;

import java.io.IOException;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

import tools.communication.CommunicationChannel;
import tools.communication.CommunicationConfig;


/**
 * @author francoise.perrin -
 * Inspiration Jacques SARAYDARYAN, Adrien GUENARD -
 *
 * 
 */
public abstract class AbstractChannel implements CommunicationChannel  {

	protected BlockingQueue<Object> msgQueue;
	protected CommunicationConfig config;
	int num = 0;

	public AbstractChannel(CommunicationConfig config, BlockingQueue<Object> msgQueue)  {
		this.config=config;
		this.msgQueue = msgQueue;
	}

	public abstract void closeChannel() throws IOException;
	public abstract void openConnection() throws IOException;
	public abstract void writeMessage(Object message);

	
	/* (non-Javadoc)
	 * @see communication.CommunicationChannel#readMessage()
	 * 
	 * Lit les messages arrivés dans la file de message
	 */
	public Object readMessage(){
		Object message=null;
		try {
			message = this.msgQueue.poll(this.config.getReadWaitTime(), TimeUnit.MILLISECONDS);
			
		} catch (InterruptedException e) {
			System.err.println("Erreur lors de la lecture de donn�es "+e.getMessage());
		}
		return message;
	}

}
