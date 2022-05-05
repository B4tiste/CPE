package tools.communication;

import java.io.IOException;

/**
 * @author francoise.perrin -
 * Inspiration Jacques SARAYDARYAN, Adrien GUENARD -
 *
 * 
 */
public interface CommunicationChannel  {
	
	public void openConnection() throws IOException;
	public void closeChannel() throws IOException;

	public Object readMessage();
	public void writeMessage(Object message);
}
