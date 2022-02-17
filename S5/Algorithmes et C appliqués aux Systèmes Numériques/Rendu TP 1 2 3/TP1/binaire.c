#include <stdio.h>
#include <math.h>

int puissance(int x, int y);

int main(int argc, char const *argv[])
{
    int n = 0;

    // Demander à l'utilisateur de saisir la valeur de n
    printf("Saisir la valeur de n : ");
    scanf("%d", &n);

    // Copie de n pour l'affichage final
    int n_copy = n;

    // Conversion de n en binaire
    int binaire = 0;
    int reste = 0;
    int i = 0;
    
    // Division euclidienne par 2
    while (n != 0)
    {
        reste = n % 2;
        binaire = binaire + reste * puissance(10, i);
        n = n / 2;
        i++;
    }

    // Afficher le résultat
    printf("%d en binaire est %d\n", n_copy, binaire);

    return 0;
}

// Fonction pour éviter d'utiliser pow()
int puissance(int x, int y)
{
    int res = 1;

    // Boucle pour calculer la puissance
    for (int i = 0; i < y; i++)
    {
        res *= x;
    }

    return res;
}