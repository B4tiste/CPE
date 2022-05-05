package tools.communication;

/**
 * @author  Jacques SARAYDARYAN, Adrien GUENARD -
 *
 * 
 */
public class CommunicationConfig{
	
	private String ip;
	private int port;
	private int readWaitTime=30000;
	
	public CommunicationConfig(String ip,int port,int readWaitTime) {
		this.ip = ip;
		this.port = port;
		this.readWaitTime=readWaitTime;
	}
	
	
	public String getIp() {
		return ip;
	}
	
	public int getPort() {
		return port;
	}
	
	public int getReadWaitTime() {
		return readWaitTime;
	}

}
