#include <stdio.h>
#include "fichier.h"

#define TAILLE_MAX 1000


int lire_fichier(char *nom_de_fichier)
{
    FILE *fichier;
    char chaine[TAILLE_MAX];

    fichier = fopen(nom_de_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }

    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
        printf("%s", chaine);
    }

    fclose(fichier);
    return 1;
}


int ecrire_dans_fichier(char *nom_de_fichier, char *message)
{
    FILE *fichier;
    fichier = fopen(nom_de_fichier, "a");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }
    fprintf(fichier, "%s\n", message);
    fclose(fichier);
    return 0;
}