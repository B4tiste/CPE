#include <stdio.h>
#include <time.h>

void srand(unsigned int seed);
int rand(void);

#define TAILLE 10

int main(int argc, char const *argv[])
{
    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL)); 

    // Consigne : 
    //  Deux tableaux : int et float
    //  Remplir les tableaux de valeurs aléatoires
    //  On parcourt les deux tableaux : 
    //  if(i%2 == 0) tab[i] = tab[i] * 3
    //  Ne pas utiliser la notation indicielle

    int tab_int[TAILLE];
    float tab2_float[TAILLE];

    // Remplissage des tableaux avec des valeurs aléatoires entre 0 et 100
    for (int i = 0; i < 10; i++)
    {
        tab_int[i] = rand() % 100;
        tab2_float[i] = rand() % 100;
    }

    // Afficher les tableaux de base
    printf("\n");
    printf("Tableau d'int de base :\n");
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%d ", tab_int[i]);
    }
    printf("\n\n");

    printf("Tableau de float de base :\n");
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%.2f ", tab2_float[i]);
    }
    printf("\n\n");

    // Declaration d'un pointeur sur le tableau d'entier
    int *ptr_int = tab_int;
    
    for (int i = 0; i < TAILLE; i++)
    {
        if(i%2 == 0)
        {
            *(ptr_int + i) = *(ptr_int + i) * 3;
        }
    }
    
    // Declaration d'un pointeur sur le tableau de float
    float *ptr_float = tab2_float;

    for (int i = 0; i < TAILLE; i++)
    {
        if(i%2 == 0)
        {
            *(ptr_float + i) = *(ptr_float + i) * 3;
        }
    }

    // Afficher les tableaux
    printf("Tableau d'int modifie :\n");
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%d ", tab_int[i]);
    }

    printf("\n\n");

    printf("Tableau de float modifie :\n");
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%.2f ", tab2_float[i]);
    }

    printf("\n\n");

    return 0;
}