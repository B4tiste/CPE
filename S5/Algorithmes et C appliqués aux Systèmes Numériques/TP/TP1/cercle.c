#include <math.h>
#include <stdio.h>

float c_aire(float r);
float c_perim(float r);

int main(int argc, char const *argv[])
{

    float rayon = 0;

    // Saisie du rayon du cercle par l'utilisateur
    printf("Entrer le rayon du cercle : ");
    // fflush(stdin);
    scanf("%f", &rayon);

    // Calcul de l'aire et du périmètre du cercle
    printf("Aire du cercle = %f\n", c_aire(rayon));
    printf("Perimetre du cercle = %f\n", c_perim(rayon));

    return 0;
}

// Fonction qui calcule l'aire d'un cercle
float c_aire(float r)
{
    float aire = M_PI * r * r;

    return aire;
}

// Fonction qui calcule le périmètre d'un cercle
float c_perim(float r)
{
    float perim = 2 * M_PI * r;

    return perim;
}