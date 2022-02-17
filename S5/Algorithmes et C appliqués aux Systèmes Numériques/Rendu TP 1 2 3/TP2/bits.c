#include <stdio.h>

#define TAILLE 20

int main(int argc, char const *argv[])
{

    int r, n = 0;
    int dec = 0b00010000000000000001; // Output : 1 
    int dec = 0b00010000000000000010; // Output : 0

    // Convertir dec en tableau de bits
    int tab[TAILLE];
    for (int i = 0; i < TAILLE; i++)
    {
        tab[i] = dec & 1;
        dec = dec >> 1;
    }

    // Le tableau tab est inversé, donc 20 --> 0 et 4 --> 16
    printf("%u", tab[0] & tab[16]);

    return 0;
}
