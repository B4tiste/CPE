#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

void srand(unsigned int seed);
int rand(void);

#define MAX 999

int main(int argc, char const *argv[])
{
    // remplir un tableau de nombres aléatoires
    int tbl[100]; // Tableaux de 100 nombres
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    for (int i = 0; i < 100; i++)
    {
        tbl[i] = rand() % MAX; // Remplir le tableau avec des nombres aléatoires
    }

    // afficher le tableau
    printf("Tableau : \n");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", tbl[i]);
    }
    printf("\n");

    // trier le tableau
    int tmp;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (tbl[i] < tbl[j])
            {
                tmp = tbl[i];
                tbl[i] = tbl[j];
                tbl[j] = tmp;
            }
        }
    }

    // afficher le tableau
    printf("Tableau : \n");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", tbl[i]);
    }
    printf("\n");

    // recherche dichotomique
    int recherche = 0; // nombre à rechercher
    int gauche = 0;
    int droite = 99;
    int milieu;
    bool trouve = false;

    printf("Entrer un nombre a chercher dans le tableau : ");
    // fflush(stdin);
    scanf("%d", &recherche);

    while (gauche <= droite && !trouve)
    {
        milieu = (gauche + droite) / 2;
        if (tbl[milieu] == recherche)
        {
            trouve = true;
        }
        else if (tbl[milieu] > recherche)
        {
            droite = milieu - 1;
        }
        else
        {
            gauche = milieu + 1;
        }
    }

    if (trouve)
    {
        printf("%d est dans le tableau\n", recherche);
    }
    else
    {
        printf("%d n'est pas dans le tableau\n", recherche);
    }


    return 0;
}
