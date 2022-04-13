package atelier2.model;


import java.util.List;

import atelier2.nutsAndBolts.PieceSquareColor;

public interface PieceModel extends Comparable<PieceModel> {
	
	
	/**
	 * @return the coord
	 */
	public char getColonne() ;
	public int getLigne() ;
	
	/**
	 * @param coord
	 * @return true si la pi�ce est aux coordonn�es pass�es en param�tre
	 */
	public boolean hasThisCoord(Coord coord);
	
	/**
	 * @param coord the coord to set
	 * le d�placement d'une pi�ce change ses coordonn�es
	 */
	public void move(Coord coord);


	/**
	 * @return the pieceColor
	 */
	public PieceSquareColor getPieceColor() ;
	
	
	/**
	 * @param targetCoord
	 * @param isPieceToCapture
	 * @return true si le d�placement est l�gal
	 */
	public boolean isMoveOk(Coord targetCoord, boolean isPieceToCapture);

	/**
	 * @param targetCoord
	 * @return liste des coordonn�es des cases travers�es par itin�raire de d�placement
	 */
	public List<Coord> getCoordsOnItinerary(Coord targetCoord);

    /**
	 * @return la liste des nouvelles destinations possibles de la pi�ce en cas de rafle
	 * i.e les cases en diagonale avec une distance d'au moins 2 cases
	 */
	public List<Coord> getTargetCoordsInMultiJumpCase();

	
}

