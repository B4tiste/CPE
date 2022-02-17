#include <stdio.h>

int main(int argc, char const *argv[])
{

    int a;

    /*
        Liste des types de données :
        char
        short
        int
        long int
        long long int
        float
        double
        long double
    */
   
    // Affichage de la taille de chaque type de variable   

    printf("Taille d'un char : %d\n", sizeof(char));
    printf("Taille d'un short : %d\n", sizeof(short));
    printf("Taille d'un int : %d\n", sizeof(int));
    printf("Taille d'un long int : %d\n", sizeof(long int));
    printf("Taille d'un long long int : %d\n", sizeof(long long int));
    printf("Taille d'un float : %d\n", sizeof(float));
    printf("Taille d'un double : %d\n", sizeof(double));
    printf("Taille d'un long double : %d\n", sizeof(long double));

    return 0;
}
