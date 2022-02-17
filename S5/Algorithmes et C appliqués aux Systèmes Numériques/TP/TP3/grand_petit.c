#include <stdio.h>
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

    /* Minimum */

    int min = MAX + 1;

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        if(tbl[i] < min)
        {
            min = tbl[i];
        }
    }

    /* Maximum */

    int max = MIN + 1;

    for (unsigned int i = 0; i < TAILLE; i++)
    {
        if(tbl[i] > max)
        {
            max = tbl[i];
        }
    }
    
    printf("Le minimum du tableau est : %i\n", min);
    printf("Le maximum du tableau est : %i\n", max);

    return 0;
}

signed short hasard(signed short a, signed short b)
{
    signed short vrdm;

    vrdm = a + rand()%(b - a + 1);

    return vrdm;
}