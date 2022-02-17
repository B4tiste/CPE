#include <stdio.h>
#include "fichier.h"
#include <string.h>

/*
    Pour compiler
    gcc -Wall -c ./fichier.c ./etudiant_bd.c
    gcc -o etudiant_bd ./fichier.o ./etudiant_bd.o
*/

// structure etudiant : 
// nom, prenom, adresse, noteC, noteOS
struct etudiant {
    char nom[20];
    char prenom[20];
    char adresse[30];
    char noteC;
    char noteOS;
};

int main(int argc, char const *argv[])
{
    
    // creer un tableau de 5 etudiants
    struct etudiant etudiants[5];

    // remplir le tableau
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("Etudiant %d\n", i+1);
        printf("Nom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].nom);
        printf("Prenom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].prenom);
        printf("Adresse : ");
        fflush(stdin);
        scanf("%s", etudiants[i].adresse);
        printf("Note C : ");
        fflush(stdin);
        scanf("%c", &etudiants[i].noteC);
        printf("Note OS : ");
        fflush(stdin);
        scanf("%c", &etudiants[i].noteOS);
    }

    for (i = 0; i < 5; i++)
    {
        // concatener les champs nom, prenom, adresse, noteC, noteOS
        char string_final[100];
        strcpy(string_final, etudiants[i].nom);
        strcat(string_final, ", ");
        strcat(string_final, etudiants[i].prenom);
        strcat(string_final, ", ");
        strcat(string_final, etudiants[i].adresse);
        strcat(string_final, ", ");
        strcat(string_final, &etudiants[i].noteC);
        strcat(string_final, ", ");
        strcat(string_final, &etudiants[i].noteOS);
    
        // ecrire dans un fichier
        ecrire_dans_fichier("etudiant_bd.txt", string_final);

    }
    
    // afficher le contenu d'un fichier
    lire_fichier("etudiant_bd.txt");

    return 0;
}
