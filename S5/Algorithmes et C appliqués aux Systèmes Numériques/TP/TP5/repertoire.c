#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "lib/repertoire.h"

/*

*/

int main()
{

    int choix = 0;
    
    char *path = "..";

    printf("\n Path : %s\n", path);
    printf("\n\t Choix de la fonction a executer : \n");
    printf("\t1 - lire_dossier(PATH)\n");
    printf("\t2 - lire_dossier_recursif('PATH')\n");
    printf("\t3 - lire_dossier_iteratif('PATH')\n");
    fflush(stdin);
    scanf("%d", &choix);

    printf("\n\n");

    switch(choix)
    {
        case 1:
            lire_dossier(path);
            break;

        case 2:
            lire_dossier_recursif(path);
            break;
        case 3:
            lire_dossier_iteratif(path);
            break;
        default:
            printf("\n Choix invalide");
            break;
    }

    return 0;
}

// Fonction lire_dossier permettant d'afficher le contenu d'un dossier
void lire_dossier(char *chemin)
{
    DIR *rep;
    struct dirent *ent;
    rep = opendir(chemin);
    if (rep == NULL)
    {
        printf("Erreur d'ouverture du dossier");
        exit(EXIT_FAILURE);
    }

    printf("Contenu du dossier %s : \n", chemin);

    while ((ent = readdir(rep)) != NULL)
    {
        printf("%s\n", ent->d_name);
    }
    closedir(rep);
}

// Fonction lire_dossier_recursif permettant d'afficher le contenu de sous-dossier de façon récursive
void lire_dossier_recursif(char *chemin)
{
    DIR *rep;
    struct dirent *ent;
    struct stat buf;
    rep = opendir(chemin);
    if (rep == NULL)
    {
        printf("Erreur d'ouverture du dossier");
        exit(EXIT_FAILURE);
    }

    printf("Contenu du dossier %s : \n", chemin);

    while ((ent = readdir(rep)) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
        {
            char *chemin_fichier = malloc(sizeof(char) * (strlen(chemin) + strlen(ent->d_name) + 2));
            strcpy(chemin_fichier, chemin);
            strcat(chemin_fichier, "/");
            strcat(chemin_fichier, ent->d_name);
            stat(chemin_fichier, &buf);
            if (S_ISDIR(buf.st_mode))
            {
                lire_dossier_recursif(chemin_fichier);
            }
            else
            {
                printf("%s\n", chemin_fichier);
            }
            free(chemin_fichier);
        }
    }
    closedir(rep);
}

// Fonction lire_dossier_iteratif permettant d'afficher le contenu de sous-dossier sans récursivité
void lire_dossier_iteratif(char *chemin)
{
    DIR *rep;
    struct dirent *ent;
    struct stat buf;

    char chemins[100][100];

    strcpy(chemins[0], chemin);

    printf("Contenu du dossier %s : \n", chemin);

    // Tant que chemins[0] n'est pas vide, afficher le contenu de chemins[0]
    // if chemins[0] est vide, alors on décale le tableau de 1 case vers la gauche
    // et on affiche le contenu de chemins[0]
    while (strcmp(chemins[0], "") != 0)
    {
        printf("\n\t## Scan du dossier %s ##\n", chemins[0]);

        rep = opendir(chemins[0]);
        if (rep == NULL)
        {
            printf("Erreur d'ouverture du dossier %s", chemins[0]);
            exit(EXIT_FAILURE);
        }
        int i = 0;
        while ((ent = readdir(rep)) != NULL)
        {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                char *chemin_fichier = malloc(sizeof(char) * (strlen(chemins[0]) + strlen(ent->d_name) + 2));
                strcpy(chemin_fichier, chemins[0]);
                strcat(chemin_fichier, "/");
                strcat(chemin_fichier, ent->d_name);
                stat(chemin_fichier, &buf);
                if (S_ISDIR(buf.st_mode))
                {
                    strcpy(chemins[i + 1], chemin_fichier);
                    i++;
                    printf("%s DOSSIER\n", chemin_fichier);
                }
                else
                {
                    printf("%s\n", chemin_fichier);
                }
                free(chemin_fichier);
            }
        }
        closedir(rep);
        strcpy(chemins[0], chemins[1]);
        for (int j = 1; j < 10; j++)
        {
            strcpy(chemins[j], chemins[j + 1]);
        }
    }
}