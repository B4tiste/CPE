package atelier3.launcher.clientServerLauncher;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import atelier3.controller.Mediator;
import atelier3.controller.clientServerControler.ControllerClient;
import atelier3.gui.GuiConfig;
import atelier3.gui.View;
import atelier3.nutsAndBolts.PieceSquareColor;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import tools.communication.ClientChannel;
import tools.communication.CommunicationChannel;
import tools.communication.CommunicationConfig;



/**
 * @author francoise.perrin.
 * Lance l'ex�cution d'un jeu de dames cot� CLIENT BLANC o� existent
 * une instance de view et une instance ControlerClient
 * Ce client peut fonctionner avec 1 serveur et 1 client NOIR
 * le server est munis d'une instance de model et d'une instance de ControlerServer
 */
public class LauncherWhiteClient extends Application {

	private EventHandler<MouseEvent> controllerClient;
	private View view;
	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		LauncherWhiteClient.launch();
	}

	@Override
	public void init () throws Exception {
		super.init();
		
		CommunicationConfig config = new CommunicationConfig("127.0.0.1", 5555, 200);
		BlockingQueue<Object> msgQueue = new ArrayBlockingQueue<Object>(20);
		CommunicationChannel cltChannel = new ClientChannel(config, msgQueue); 
		
		this.controllerClient = new ControllerClient(cltChannel, PieceSquareColor.WHITE);
		
		this.view = new View(this.controllerClient);

		((Mediator) this.controllerClient).setView(this.view);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		primaryStage.setScene(new Scene(this.view,  GuiConfig.HEIGHT, GuiConfig.HEIGHT));
		primaryStage.setTitle("Jeu de dames - Client blanc");
		primaryStage.setX(10);
		primaryStage.setY(150);
		primaryStage.show();
	}
}
