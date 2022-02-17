#include <stdio.h>
#include <math.h>

void fibonacci(int x);

int main(int argc, char const *argv[])
{

    int n;

    // On demande à l'utilisateur la valeur de n
    printf("Entrer N : ");
    // fflush(stdin);
    scanf("%i", &n);

    // on calcule les n premiers termes de la suite de Fibonacci
    fibonacci(n);

    return 0;
}

// Fonction qui calcule les n premiers termes de la suite de Fibonacci
void fibonacci(int x)
{
    int suivant;
    int u0 = 0;
    int u1 = 1;

    for (int i = 0; i < x; i++)
    {
        // On calcule le n-ième terme de la suite de Fibonacci
        if (i <= 1)
        {
            suivant = i;
        }
        else
        {
            suivant = u0 + u1;
            u0 = u1;
            u1 = suivant;
        }
        printf("%d ", suivant);
    }

    printf("\n");
}