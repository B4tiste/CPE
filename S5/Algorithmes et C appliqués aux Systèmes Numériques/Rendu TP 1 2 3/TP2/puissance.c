#include <stdio.h>

int puissance(int x, int y);

int main(int argc, char const *argv[])
{
    int a, b;

    printf("== Calcul de a puissance b ==\n");

    // On demande les valeurs a et b à l'utilisateur
    printf("Entrer 'a' : ");
    // fflush(stdin);
    scanf("%i", &a);

    printf("Entrer 'b' : ");
    // fflush(stdin);
    while(getchar() != '\n');
    scanf("%i", &b);

    // On affiche la valeur de a puissance b
    printf("Resulat de %i^%i = %i\n", a, b, puissance(a, b));

    return 0;
}

// Fonction qui calcule la puissance de a à la puissance de b
int puissance(int x, int y)
{
    int res = 1;

    // Boucle qui calcule la puissance de a à la puissance de b
    for (int i = 0; i < y; i++)
    {
        res *= x;
    }

    return res;
}