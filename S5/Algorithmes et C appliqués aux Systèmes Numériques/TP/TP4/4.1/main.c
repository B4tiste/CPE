#include <stdio.h>
#include "operator.h"

/*
    pour compiler : 
    gcc -Wall -c ./operator.c ./main.c
    gcc -o main ./operator.o ./main.o
*/

int main(int argc, char const *argv[])
{

    // demander deux nombres et un operateur
    int nb1, nb2;
    char op;
    long int resultat;

    printf("a");

    printf("Entrer la valeur de num1 : ");
    fflush(stdin);
    scanf("%i", &nb1);

    printf("\nEntrer la valeur de num1 : ");
    fflush(stdin);
    scanf("%i", &nb2);

    while (1)
    {
        printf("Entrer l'operateur choisis entre [+, -, *, /, %%, &, |, ~] : ");
        fflush(stdin);
        scanf("%c", &op);

        switch (op)
        {
        case '+':
            resultat = somme(nb1, nb2);
            break;
        case '-':
            resultat = soustraction(nb1, nb2);
            break;
        case '*':
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


        printf("Le resultat de %i %c %i est : %ld \n\n", nb1, op, nb2, resultat);
    }

    return 0;
}
