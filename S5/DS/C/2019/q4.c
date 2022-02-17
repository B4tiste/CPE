#include <stdio.h>

void echange(int *a, int *b);

int main(int argc, char const *argv[])
{
    
    int a = 5;
    int b = 10;

    printf("Valeur de a et b avant l'appel de la fonction : %d et %d\n", a, b);
        
    echange(&a, &b);

    printf("Valeur de a et b après l'appel de la fonction : %d et %d\n", a, b);

    return 0;
}

void echange(int *a, int *b)
{
    int c;
    c = *a;
    *a = *b;
    *b = c;
}