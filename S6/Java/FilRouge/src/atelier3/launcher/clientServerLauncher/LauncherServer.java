package atelier3.launcher.clientServerLauncher;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import atelier3.controller.Mediator;
import atelier3.controller.clientServerControler.ControllerServer;
import atelier3.model.BoardGame;
import atelier3.model.Coord;
import atelier3.model.Model;
import javafx.application.Application;
import javafx.stage.Stage;
import tools.communication.CommunicationChannel;
import tools.communication.CommunicationConfig;
import tools.communication.ServerChannel;



/**
* @author francoise.perrin.
* Lance l'ex�cution d'un jeu de dames cot� SERVER o� existent :
* 		1 instance du model, 
* 		1 instance du controler cot� Model : ControllerServer
* 		0 instance de view
* 
* Ce serveur fonctionne avec 2 clients (NOIR et BLANC)
* chacun munis d'une instance de view et d'une instance de ControllerClient
* 
*/
public class LauncherServer extends Application {


	private BoardGame<Coord> model;
	private BoardGame<Integer> controllerModel;

	private CommunicationConfig config = new CommunicationConfig("127.0.0.1", 5555,200);;
	private BlockingQueue<Object> msgQueue = new ArrayBlockingQueue<Object>(20);
	private CommunicationChannel srvChannel = new ServerChannel(config, msgQueue);

	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		LauncherServer.launch();
	}

	@Override
	public void init () throws Exception {
		super.init();
		this.model = new Model();
		this.controllerModel = new ControllerServer(this.srvChannel);

		((Mediator) this.controllerModel).setModel(this.model);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		
	}
}

