package atelier2.controller;

import atelier2.gui.View;
import atelier2.model.BoardGame;
import atelier2.model.Coord;

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
