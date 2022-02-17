#include <stdio.h>
#include <stdlib.h>

// Commande de compilation : gcc -Wall -o main main.c

// Fonction pour convertir une chaine de caracteres en entier
int conversion( char * str)
{
    int i = 0;
    int nombre = 0;
    int signe = 1;
    
    if (str[0] == '-')
    {
        signe = -1;
        i++;
    }
    
    while (str[i] != '\0')
    {
        nombre = nombre * 10 + (str[i] - '0');
        i++;
    }
    
    return nombre * signe;
}

// Fonction trier qui prend en paramètre un tableau de nombres et qui l'affiche dans l'ordre croissant
void trier(int *tab, int n) {
    int i, j, tmp;
    
    //Tri à bulle croissant
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                tmp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
        }
    }
    for (i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    // Afficher le tableau dans l'ordre décroissant
    for (i = n - 1; i >= 0; i--) {
        printf("%d ", tab[i]);
    }

    printf("\n");
}

int main(int argc, char const *argv[])
{
    // Afficher le nombre de ligne du fichier de nom argv[1]

    // 1. Ouvrir le fichier en lecture
    FILE *f = fopen(argv[1], "r");

    // 2. Compter le nombre de ligne
    int nbLignes = 0;
    char c;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
        {
            nbLignes++;
        }
    }

    // 3. Afficher le nombre de ligne
    printf("Nombre de ligne du fichier %s : %d\n", argv[1], nbLignes + 1);

    // 4. Fermer le fichier
    fclose(f);

    // Creer un tableau de nombres
    int tab[6] = {0, 5, 3, 2, 1, 4};

    // Afficher le tableau
    printf("Tableau : ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    // Appeler la fonction trier
    trier(tab, 6);

    char str[100];
    printf("Entrez un nombre : ");
    scanf("%s", str);
    printf("%d\n", conversion(str));

    return 0;
}

