#include <stdio.h>
#include <stdlib.h>
#include "operator.h"

/*
    pour compiler : 
    gcc -Wall -c ./calcule.c ./operator.c
    gcc -o calcule ./calcule.o ./operator.o
*/


/*
    Utilisation du programme :
    $ calcul [operateur] [nombre1] [nombre2]
    [operateur] : +, -, x, /, %, &, |, ~
    Exemple :
        > calcul + 2 3
        > 5
*/

int main(int argc, char const *argv[])
{
    int nb1 = atoi(argv[2]), nb2 = atoi(argv[3]);
    char operateur = *argv[1];

    long int resultat;
    
    printf("Nombre d'arguments : %d\n", argc);

    // afficher le contenu de argv
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    printf("\n");

    /*
    switch (operateur)
        {
        case '+':
            resultat = somme(nb1, nb2);
            break;
        case '-':
            resultat = soustraction(nb1, nb2);
            break;
        // case '*':
        case 'x': // Utilisation d'un char 'x' pour '*' sur Windows
            resultat = multiplication(nb1, nb2);
            break;
        case '/':
            resultat = division(nb1, nb2);
            break;
        case '%':
            resultat = modulo(nb1, nb2);
            break;
        case '&':
            resultat = et(nb1, nb2);
            break;
        case '|':
            resultat = ou(nb1, nb2);
            break;
        case '~':
            resultat = negation(nb1);
            break;
        default:
            printf("\nErreur : operateur non reconnu\n");
            break;
        }
    */

        // printf("Le resultat de %i %c %i est : %ld \n\n", nb1, operateur, nb2, resultat);
    
    return 0;
}