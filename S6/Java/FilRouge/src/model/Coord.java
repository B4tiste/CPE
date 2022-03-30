package model;

import java.util.function.ToIntFunction;

/**
 * @author francoiseperrin
 *
 *         Coordonn�es des PieceModel
 */
public class Coord implements Comparable<Coord> {

    private char colonne; // ['a'..'j']
    private int ligne; // [10..1]
    static final int MAX = ModelConfig.LENGTH; // 10

    public Coord(char colonne, int ligne) {
        super();
        this.colonne = colonne;
        this.ligne = ligne;
    }

    public char getColonne() {
        return colonne;
    }

    public int getLigne() {
        return ligne;
    }

    @Override
    public String toString() {
        return "[" + ligne + "," + colonne + "]";
    }

    @Override
    public boolean equals(Object c) {

        boolean ret = false;

        if (c.getClass() != this.getClass()) {
            ret = false;
        }

        else if (this.ligne == ((Coord) c).ligne && this.colonne == ((Coord) c).colonne) {
            ret = true;
        }

        return ret;
    }

    /**
     * @param coord
     * @return true si 'a' <= col < 'a'+MAX et 1 < lig <= MAX
     */
    public static boolean coordonnees_valides(Coord coord) {

        boolean ret = false;

        char col = coord.getColonne();
        int lig = coord.getLigne();

        if ('a' <= col && col < 'a' + MAX && 1 < lig && lig <= MAX) {
            ret = true;
        }

        return ret;
    }

    /*
     * (non-Javadoc)
     * 
     * @see java.lang.Comparable#compareTo(java.lang.Object)
     * 
     * La m�thode compareTo() indique comment comparer un objet � l'objet courant
     * selon l'ordre dit naturel
     * Dans cet application, nous d�cidons que l'ordre naturel est celui
     * correspondant au N� de la case d'un tableau 2D repr�sent� par la Coord
     * ainsi le N� 1 correspond � la Coord ['a', 10], le N� 100 correspond � la
     * Coord ['j', 1]
     */
    @Override
    public int compareTo(Coord o) {
        int ret = 999;

        // TODO Atelier 1

        int score_a = (int) (this.getColonne() - 96) + 10 * (10 - this.getLigne());
        int score_b = (int) (o.getColonne() - 96) + 10 * (10 - o.getLigne());

        ret = score_a - score_b;

        return ret;
    }

}
