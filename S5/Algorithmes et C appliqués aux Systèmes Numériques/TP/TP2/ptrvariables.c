#include <stdio.h>

int main(int argc, char const *argv[])
{
    
    // Liste de type : char, short, int, long int, long long int, float, double, long double

    // Declaration des variables
    char t1;
    short t2;
    int t3;
    long int t4;
    long long int t5;
    float t6;
    double t7;
    long double t8;

    /*
    int a = 0;
    int *b = &a;

    a++;

    printf("%d\n", a);

    (*b)++;

    printf("%d\n", a);
    */

    // affecter des pointeurs aux variables
    char *p1 = &t1;
    short *p2 = &t2;
    int *p3 = &t3;
    long int *p4 = &t4;
    long long int *p5 = &t5;
    float *p6 = &t6;
    double *p7 = &t7;
    long double *p8 = &t8;

    // Affectation des valeurs
    *p1 = 'a';
    *p2 = 1;
    *p3 = 2;
    *p4 = 3;
    *p5 = 4;
    *p6 = 5.0;
    *p7 = 6.0;
    *p8 = 7.0;

    // Affichage : type de la variable, adresse de la variable, valeur de la variable
    printf("Type : %s | Adresse : %p | Valeur : %c\n", "char", p1, *p1);
    printf("Type : %s | Adresse : %p | Valeur : %d\n", "short", p2, *p2);
    printf("Type : %s | Adresse : %p | Valeur : %d\n", "int", p3, *p3);
    printf("Type : %s | Adresse : %p | Valeur : %ld\n", "long int", p4, *p4);
    printf("Type : %s | Adresse : %p | Valeur : %lld\n", "long long int", p5, *p5);
    printf("Type : %s | Adresse : %p | Valeur : %f\n", "float", p6, *p6);
    printf("Type : %s | Adresse : %p | Valeur : %f\n", "double", p7, *p7);
    printf("Type : %s | Adresse : %p | Valeur : %Lf\n", "long double", p8, *p8);

    return 0;
}