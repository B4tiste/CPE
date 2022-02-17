#include <stdio.h>

int main(int argc, char const *argv[])
{

    int compter;

    // On demande à l'utilisateur de saisir la taille de la pyramide
    printf("Entrer la taille du triangle (min 5) : ");
    // fflush(stdin);
    scanf("%i", &compter);

    // Si la taille est inférieure à 5, on affiche un message d'erreur
    if (compter < 4)
    {
        printf("Taille de triangle trop petite...");
    }
    // Sinon on affiche la pyramide
    else
    {
        for (int i = 0; i < compter; i++)
        {
            // On affiche la première ligne
            if (i == 0)
            {
                printf("*");
            }

            // On affiche les lignes suivantes
            else if (i < compter - 1)
            {
                printf("* ");

                for (int j = 0; j < i - 1; j++)
                {
                    printf("# ");
                }

                printf("*");
            }

            // On affiche la derniere ligne
            else
            {
                for (int j = 0; j < compter; j++)
                {
                    printf("* ");
                }
            }

            printf("\n");
        }
    }

    return 0;
}