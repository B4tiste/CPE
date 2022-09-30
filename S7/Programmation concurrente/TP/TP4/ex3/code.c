#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define QUANTITE 10

// Fonction d'aléatoire
void srand(unsigned int seed);
int hasard(int a, int b);

int main()
{
    // Init random seed
    srand((unsigned int)time(0));

    /*
            Un premier processus, appelé Générateur, génère N nombres aléatoires positifs ou nuls. Si le
        nombre généré est pair (respectivement impair) alors il est déposé dans le tube NombresPairs (respectivement
        NombresImpairs) - à la fin de la génération, ce processus dépose la valeur -1 dans les 2 tubes (pour
        indiquer la fin de la série des nombres). Ensuite, il récupère les deux nombres déposés
        respectivement dans le tube SommePairs et SommeImpairs, réalise leur somme et affiche le résultat.

            Un deuxième processus, appelé FiltrePair est chargé de récupérer les nombres déposés dans le tube
        NombresPairs, de réaliser la somme de ces nombres et de déposer le résultat dans le tube SommePairs.

            Un troisième processus, appelé FiltreImpair est chargé de récupérer les nombres déposés dans le tube
        NombresImpairs, de réaliser la somme de ces nombres et de déposer le résultat dans le tube
        SommeImpairs.
    */

   // Création des tubes
    int tubePair[2], tubeImpair[2], sommePair[2], sommeImpair[2];

    // Create pipes
    pipe(tubePair);
    pipe(tubeImpair);
    pipe(sommePair);
    pipe(sommeImpair);

    // Create processes
    int generateur = fork();
    int filtrePair = fork();
    int filtreImpair = fork();

    int nombres[QUANTITE];

    // Si on est dans le générateur
    if (generateur == 0)
    {
        // On génère dix nombres alétoires
        for (int i = 0; i < QUANTITE; i++)
        {
            int rdmNbr = hasard(0, 10);

            nombres[i] = rdmNbr;

            // Si il est impair
            if (rdmNbr % 2)
            {
                write(tubeImpair[1], &rdmNbr, sizeof(int));
            }
            // Si il est pair
            else
            {
                write(tubePair[1], &rdmNbr, sizeof(int));
            }
        }

        // On dépose la valeur -1 dans les 2 tubes pour indiquer la fin de la série des nombres
        int end = -1;
        write(tubePair[1], &end, sizeof(int));
        write(tubeImpair[1], &end, sizeof(int));

        // On récupère les deux nombres déposés respectivement dans le tube SommePairs et SommeImpairs
        int sommeP, sommeI;
        read(sommePair[0], &sommeP, sizeof(int));
        read(sommeImpair[0], &sommeI, sizeof(int));

        // On réalise leur somme et on affiche le résultat
        printf("Somme des deux tubes : %d + %d = %d \n", sommeP, sommeI, sommeP + sommeI);

        for (size_t i = 0; i < QUANTITE; i++)
        {
            printf("%d ", nombres[i]);
        }

        printf("\n");
        

        // for (int j = 0; j < 2; j++)
        // {
        //     close(tubeImpair[j]);
        //     close(tubePair[j]);
        //     close(sommeImpair[j]);
        //     close(sommePair[j]);
        // }
    }
    else
    {
        // Si on est dans le filtrePair
        if (filtrePair == 0)
        {
            int sommeP = 0;
            int nbr;

            // On récupère les nombres déposés dans le tube NombresPairs
            while (read(tubePair[0], &nbr, sizeof(int)) > 0)
            {
                // Si le nombre est -1
                if (nbr == -1)
                {
                    // On dépose le résultat dans le tube SommePairs
                    write(sommePair[1], &sommeP, sizeof(int));
                    break;
                }
                else
                {
                    // On réalise la somme de ces nombres
                    sommeP += nbr;
                }
            }
        }
        else
        {
            // Si on est dans le filtreImpair
            if (filtreImpair == 0)
            {
                int sommeI = 0;
                int nbr;

                // On récupère les nombres déposés dans le tube NombresImpairs
                while (read(tubeImpair[0], &nbr, sizeof(int)) > 0)
                {
                    // Si le nombre est -1
                    if (nbr == -1)
                    {
                        // On dépose le résultat dans le tube SommeImpairs
                        write(sommeImpair[1], &sommeI, sizeof(int));
                        break;
                    }
                    else
                    {
                        // On réalise la somme de ces nombres
                        sommeI += nbr;
                    }
                }
            }
        }
    }

        return 0;
}

// Fonction d'aléatoire
int hasard(int a, int b)
{
    return a + rand() % (b - a + 1);
}
