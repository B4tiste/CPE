package tools.communication;

import java.io.IOException;
import java.io.ObjectOutputStream;

/**
 * @author francoise.perrin -
 * Inspiration Jacques SARAYDARYAN, Adrien GUENARD -
 *
 */
public class Sender  {
	private ObjectOutputStream ouputStream;

	public Sender(ObjectOutputStream ouputStream) {
		this.ouputStream = ouputStream;		
	}
	
	public void write(Object message) throws IOException{		
		this.ouputStream.writeObject(message);
		this.ouputStream.flush();
	}
	public void stop() {
		if (ouputStream != null)
			try {
				ouputStream.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
	
	}
}
