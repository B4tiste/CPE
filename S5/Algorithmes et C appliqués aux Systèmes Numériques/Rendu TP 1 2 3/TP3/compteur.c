#include <stdio.h>
#include <time.h>

void srand(unsigned int seed);
int rand(void);

typedef struct couleur {
    int rouge;
    int vert;
    int bleu;
    int alpha;
} couleur;

#define TAILLE 100
#define SAMPLE 8

int main(int argc, char const *argv[])
{
    // Init de la seed pour la génération de nombre pseudo aléatoires
    srand((unsigned int)time(NULL));

    //Creer un tableau de 8 couleurs et le remplir avec des valeurs héxadécimales aléatoires
    couleur tab_sample[SAMPLE];
    int i;
    for (i = 0; i < SAMPLE; i++)
    {
        tab_sample[i].rouge = rand() % 256;
        tab_sample[i].vert = rand() % 256;
        tab_sample[i].bleu = rand() % 256;
        tab_sample[i].alpha = rand() % 256;
    }

    /*
    //Afficher les valeurs hexadécimales de chaque couleur de tab_sample
    for (i = 0; i < SAMPLE; i++)
    {
        printf("%d %d %d %d\n", tab_sample[i].rouge, tab_sample[i].vert, tab_sample[i].bleu, tab_sample[i].alpha);
    }
    */

    //Creer un tableau de couleurs et le remplir avec des couleurs aléatoires tirées de tab_sample
    couleur tab_couleur[TAILLE];

    int n = 0;
    for (i = 0; i < TAILLE; i++)
    {
        n = rand() % SAMPLE;
        tab_couleur[i].rouge = tab_sample[n].rouge;
        tab_couleur[i].vert = tab_sample[n].vert;
        tab_couleur[i].bleu = tab_sample[n].bleu;
        tab_couleur[i].alpha = tab_sample[n].alpha;
    }

    /*
    printf("Tableau de base des couleurs : \n");

    Afficher le tableau de couleurs
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%d %d %d %d\n", tab_couleur[i].rouge, tab_couleur[i].vert, tab_couleur[i].bleu, tab_couleur[i].alpha);
    }
    */

    // Trouver les duplicatas de chaque couleurs
    int nb_couleur[TAILLE];
    for (int i = 0; i < TAILLE; i++)
    {
        nb_couleur[i] = 0;
    }

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (tab_couleur[i].rouge == tab_couleur[j].rouge &&
                tab_couleur[i].vert == tab_couleur[j].vert && 
                tab_couleur[i].bleu == tab_couleur[j].bleu && 
                tab_couleur[i].alpha == tab_couleur[j].alpha)
            {
                nb_couleur[i]++;
            }
        }
    }


    // Création d'une struct pour stocker les couleurs et leur nombre de repetition
    typedef struct compteur {
        couleur clr;
        int nb;
        int checked; // 0 = non vérifié, 1 = vérifié
    } compteur;

    compteur tab_compteur[TAILLE];

    for (int i = 0; i < TAILLE; i++)
    {
        tab_compteur[i].clr = tab_couleur[i];
        tab_compteur[i].nb = nb_couleur[i];
        tab_compteur[i].checked = 0;
    }

    /*
    printf("Tableau des couleurs et leur nombre de repetition : \n");
    for (int i = 0; i < TAILLE; i++)
    {
        printf("0x%x 0x%x 0x%x 0x%x %d \n", tab_compteur[i].clr.rouge, tab_compteur[i].clr.vert, tab_compteur[i].clr.bleu, tab_compteur[i].clr.alpha, tab_compteur[i].nb);
    }
    printf("===========================\n");
    */    
    
    for (int i = 0; i < TAILLE; i++)
    {
        if (tab_compteur[i].checked == 0)
        {
            tab_compteur[i].checked = 1;

            for (int j = 0; j < TAILLE; j++)
            {
                if (tab_compteur[j].checked == 0 &&
                    tab_compteur[i].clr.rouge == tab_compteur[j].clr.rouge &&
                    tab_compteur[i].clr.vert == tab_compteur[j].clr.vert && 
                    tab_compteur[i].clr.bleu == tab_compteur[j].clr.bleu && 
                    tab_compteur[i].clr.alpha == tab_compteur[j].clr.alpha)
                {
                    tab_compteur[j].checked = 1;
                    tab_compteur[j].nb = 0;
                }
            }
        }
    }

    printf("===========================\n");
    printf("Tableau des couleurs et le nombre de fois qu'elles apparaissent : \n");
    for (int i = 0; i < TAILLE; i++)
    {
        if (tab_compteur[i].nb != 0)
        // if (1)
        {
            printf("0x%2.2x 0x%2.2x 0x%2.2x 0x%2.2x %d \n", tab_compteur[i].clr.rouge, tab_compteur[i].clr.vert, tab_compteur[i].clr.bleu, tab_compteur[i].clr.alpha, tab_compteur[i].nb);
        }
    }

    printf("===========================\n");

    return 0;
}
