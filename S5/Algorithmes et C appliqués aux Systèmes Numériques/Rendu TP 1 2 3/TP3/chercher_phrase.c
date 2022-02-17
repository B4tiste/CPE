#include <stdio.h>

int compare(char *s1, char *s2);

int main(int argc, char const *argv[])
{
    // Creation d'un tableau de 10 phrases
    char tabPhrase[10][50] = {
        "Bonjour",
        "Au revoir",
        "Aujourd'hui",
        "Demain",
        "Nous sommes le 10",
        "Nous sommes le 11",
        "Nous sommes le 12",
        "Nous sommes le 13",
        "Nous sommes le 14",
        "Nous sommes le 15"
    };

    // creation de la chaine de caractere à chercher
    char phrase[50] = "Bonjour";

    // affiche chaque caractere de phrase
    int i;
    for (i = 0; i < 50; i++)
    {
        printf("%c", phrase[i]);
    }

    printf("\n");

    // Vérifie si la phrase est dans le tableau
    int trouve = 0;
    for (i = 0; i < 10; i++)
    {
        if (compare(tabPhrase[i], phrase) == 1)
        {
            trouve = 1;
        }
    }

    if (trouve == 1)
    {
        printf("La phrase est dans le tableau\n");
    }
    else
    {
        printf("La phrase n'est pas dans le tableau\n");
    }

    return 0;

}

// Compare deux chaines de caracteres sans utiliser strcmp, retourne 1 si elles sont egales, 0 sinon
int compare(char *s1, char *s2)
{
    int i;
    for (i = 0; i < 50; i++)
    {
        if (s1[i] != s2[i])
        {
            return 0;
        }
    }
    return 1;
}