#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBR_LIGNE 1000
#define TAILLE_LIGNE 200

/*
    Utilisation du programme :
    ./chercherfichier [MOT_A_CHERCHER] [NOM_FICHIER]
*/

int main(int argc, char const *argv[])
{
    
    // récupération de chaque ligne du fichier argv[2]
    FILE *fichier = NULL;
    char ligne[TAILLE_LIGNE]; // tableau de caractères pour stocker une ligne du fichier
    int i = 0;
    
    fichier = fopen(argv[2], "r"); // ouverture en lecture du fichier argv[2]
    
    if (fichier != NULL) // vérification de l'existance ou non du fichier
    {
        // tant qu'on a pas atteint la fin du fichier
        while (fgets(ligne, TAILLE_LIGNE, fichier) != NULL)
        {
            // trouver le nombre d'occurence du mot argv[1] dans ligne
            int nbr_occurence = 0;
            const char *mot = argv[1];
            char *ptr = strstr(ligne, mot);
            while (ptr != NULL)
            {
                nbr_occurence++;
                ptr = strstr(ptr + 1, mot);
            }
            
            if(nbr_occurence != 0)
            {
                printf("Ligne %d: %d fois\n", i + 1, nbr_occurence);
            }

            i++;
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", argv[2]);
    }    
    
    return 0;
}
