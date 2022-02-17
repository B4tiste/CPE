#include <stdio.h>
#include <stdbool.h>
#include <time.h>

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

    for (size_t i = 0; i < TAILLE; i++)
    {
        printf("%d ", tbl[i]);
    }

    int entier = 0;

    printf("Entrer l'entier a trouver dans le tableau : ");

    // fflush(stdin);
    scanf("%d", &entier);

    bool present = false;

    // tbl[0] = 20;

    for (size_t i = 0; i < TAILLE; i++)
    {
        if(tbl[i] == entier)
        {
            printf("\nL'entier %d se trouve dans le tableau au rang [%ld] !", entier, i);
            present = true;
        }
    }
    
    printf("\n");

    if (present == false)
    {
        printf("L'entier %d ne se trouve pas dans le tableau !", entier);
    }

    return 0;
}

signed short hasard(signed short a, signed short b)
{
    signed short vrdm;

    vrdm = a + rand()%(b - a + 1);

    return vrdm;
}