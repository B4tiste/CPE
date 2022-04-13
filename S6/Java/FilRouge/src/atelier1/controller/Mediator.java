package atelier1.controller;

import atelier1.gui.View;
import atelier1.model.BoardGame;
import atelier1.model.Coord;

/**
 * @author francoise.perrin
 * Le Controller fait le lien entre laView et le Model 
 * qui ne se connaissent pas
 * 
 */
public interface Mediator {
	
	public void setView(View view) ;
	public void setModel(BoardGame<Coord> model) ;
}
