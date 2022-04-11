package model;

import java.util.LinkedList;
import java.util.List;

import nutsAndBolts.PieceSquareColor;

public class PawnModel implements PieceModel {

    private Coord coord;
    private PieceSquareColor pieceColor;

    public PawnModel(Coord coord, PieceSquareColor pieceColor) {
        super();

        // TODO Atelier 1

        this.coord = coord;
        this.pieceColor = pieceColor;

    }

    @Override
    public char getColonne() {
        char colonne = ' ';

        // TODO Atelier 1

        return colonne;
    }

    @Override
    public int getLigne() {
        int ligne = -1;

        // TODO Atelier 1

        return ligne;
    }

    @Override
    public boolean hasThisCoord(Coord coord) {
        boolean hasThisCoord = false;

        // TODO Atelier 1

        return hasThisCoord;
    }

    @Override
    public PieceSquareColor getPieceColor() {
        PieceSquareColor color = null;

        // TODO Atelier 1

        return color;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        String st = null;

        switch (pieceColor) {
            case BLACK:
                st = "[B" + coord + "]";
                break;

            case WHITE:
                st = "[W[" + coord + "]]";
                break;

            default:
                break;
        }

        return st;
    }

    @Override
    public void move(Coord coord) {

        this.coord = coord;

    }

    @Override
    public boolean isMoveOk(Coord targetCoord, boolean isPieceToCapture) {
        boolean ret = false;

        String alpha = "abcdefghij";
        int id = alpha.indexOf(targetCoord.getColonne());

        if (isPieceToCapture) {
            if ((Math.abs(id - alpha.indexOf(this.coord.getColonne())) == 2)
                    && Math.abs(targetCoord.getLigne() - this.coord.getLigne()) == 2) {
                ret = true;
            } else {
                ret = false;
            }

        } else {
            if ((Math.abs(id - alpha.indexOf(this.coord.getColonne())) == 1)
                    && Math.abs(targetCoord.getLigne() - this.coord.getLigne()) == 1) {
                ret = true;
            } else {
                ret = false;
            }
        }

        return ret;
    }

    @Override
    public List<Coord> getCoordsOnItinerary(Coord targetCoord) {

        List<Coord> coordsOnItinery = new LinkedList<Coord>();

        // TODO Atelier 2

        return coordsOnItinery;
    }

}
