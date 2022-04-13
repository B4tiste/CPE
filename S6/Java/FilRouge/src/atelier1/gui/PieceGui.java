package atelier1.gui;

import atelier1.nutsAndBolts.PieceSquareColor;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;


/**
 * @author francoise.perrin
 * 
 * Cette classe permet de donner une image aux pièces
 *
 */

public class PieceGui extends ImageView implements CheckersPieceGui {
	
	// ToDo Atelier 2
	
	
	
	@Override
	public void promote(Image image) {
		
		// ToDo Atelier 2, utile pour Atelier 3
		
	}

	@Override
	public boolean hasSameColorAsGamer(PieceSquareColor gamerColor) {

		// ToDo Atelier 2, utile pour Atelier 4
		
		return false; // à changer 
	}
	
}