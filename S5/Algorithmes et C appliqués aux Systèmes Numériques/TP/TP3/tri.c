#include <stdio.h>
#include <time.h>
#include <stdbool.h>

// Fonctions de générations de nombres pseudos aléatoires
signed short hasard(signed short a, signed short b);
void srand(unsigned int seed);
int rand(void);

#define MAX 999
#define MIN 0

#define TAILLE 100

int main(int argc, char const *argv[])
{

    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL)); 
    
    int tbl[TAILLE];

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        tbl[i] = hasard(MIN, MAX);
    }

    printf("Tableau de base :\n");
    for (unsigned int i = 0; i < TAILLE; i++)
    {
        printf("%d ", tbl[i]);
    }

    /*
    
    tri_à_bulles_optimisé(Tableau T)
    pour i allant de 0 à TAILLE - 1
        tableau_trié := vrai
        pour j allant de 0 à TAILLE - i - 1
            si T[j+1] < T[j]
                (T[j+1], T[j]) = (T[j], T[j+1])
                tableau_trié := faux
        si tableau_trié
            fin tri_à_bulles_optimisé

    */

   /* Bubble sort */

    int tmp = 0;
    
    for (unsigned int i = 0; i < TAILLE - 1; i++)
    {
        bool tri = true;

        // printf("a");
        
        for (unsigned int j = 0; j < TAILLE - i - 1; j++)
        {
            // printf("%d", tbl[j+1] < tbl[j]);

            if(tbl[j+1] < tbl[j])
            {
                // printf("a");
                tmp = tbl[j];
                tbl[j] = tbl[j+1];
                tbl[j+1] = tmp;

                tri = false;
            }
        }

        if(tri)
        {
            break;
        }
        
    }

    printf("\n\n");

    printf("Tableau apres le tri :\n");

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        printf("%d ", tbl[i]);
    }
    
    return 0;
}

signed short hasard(signed short a, signed short b)
{
    signed short vrdm;

    vrdm = a + rand()%(b - a + 1);

    return vrdm;
}