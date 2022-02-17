#include <stdio.h>

// struct couleur_rgba : rouge, vert, bleu, alpha
typedef struct couleur_rgba {
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
} couleur_rgba;

int main(int argc, char const *argv[])
{
    // tableau de valeurs RGBA de 10 couleurs
    couleur_rgba tab_couleurs[10] = {
        {0x00, 0x00, 0x00, 0xFF},
        {0xFF, 0x00, 0x00, 0xFF},
        {0x00, 0xFF, 0x00, 0xFF},
        {0x00, 0x00, 0xFF, 0xFF},
        {0xFF, 0xFF, 0x00, 0xFF},
        {0x00, 0xFF, 0xFF, 0xFF},
        {0xFF, 0x00, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF},
        {0x80, 0x80, 0x80, 0xFF},
        {0xC0, 0xC0, 0xC0, 0xFF}
    }; 
    

    // affichage du tableau tab_couleur
    for (int i = 0; i < 10; i++) {
        printf("%d %d %d %d\n", tab_couleurs[i].rouge, tab_couleurs[i].vert, tab_couleurs[i].bleu, tab_couleurs[i].alpha);
    }

    return 0;
}
