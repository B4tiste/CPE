#include <stdio.h>
#include "fichier.h"

/*
    pour compiler : 
    gcc -Wall -c ./fichier.c ./main.c
    gcc -o main ./fichier.o ./main.o
*/

int main(int argc, char const *argv[])
{
    

    // afficher le contenu du fichier avant modification
    printf("Fichier avant modification : \n");
    lire_fichier("fichier.txt");

    printf("\n");

    // demander à l'utilisateur d'entrer une chaine de caractère
    char str[100];
    printf("Enter a string: ");
    fflush(stdin);
    scanf("%s", str);

    // ecrire la chaine str dans le fichier fichier.txt 
    ecrire_dans_fichier("fichier.txt", str);

    // afficher le contenu du fichier apres modification
    printf("Fichier apres modification : \n");
    lire_fichier("fichier.txt");

    return 0;
}