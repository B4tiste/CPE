#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

#define TAILLE_MAX 1000

// Fonction qui lit un fichier et renvoie le contenu dans un tableau
char *lire_fichier(char *nom_de_fichier)
{
    FILE *fichier;
    char chaine[TAILLE_MAX];
    char tab_chaine[100][TAILLE_MAX];

    fichier = fopen(nom_de_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }

    int i = 0;

    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
        strcpy(tab_chaine[i], chaine);
        i++;
    }

    fclose(fichier);
    return tab_chaine;
}

// Fonction qui ecrit message dans un fichier
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

// Fonction qui chercher une chaine dans un fichier et qui affiche le nombre de fois qu'elle apparait dans chaque ligne
int chercher_dans_fichier(char *nom_de_fichier, char *chaine_a_chercher)
{
    FILE *fichier;
    char chaine[TAILLE_MAX];
    char tab_chaine[100][TAILLE_MAX];
    int i = 0;
    int j = 0;
    int k = 0;
    int nb_occurence = 0;

    fichier = fopen(nom_de_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return -1;
    }

    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
        strcpy(tab_chaine[i], chaine);
        i++;
    }

    for (j = 0; j < i; j++)
    {
        for (k = 0; k < strlen(tab_chaine[j]); k++)
        {
            if (tab_chaine[j][k] == chaine_a_chercher[0])
            {
                if (strstr(tab_chaine[j], chaine_a_chercher) != NULL)
                {
                    nb_occurence++;
                }
            }
        }
    }

    printf("La chaine %s apparait %d fois dans le fichier %s\n", chaine_a_chercher, nb_occurence, nom_de_fichier);
    fclose(fichier);
    return 1;
}