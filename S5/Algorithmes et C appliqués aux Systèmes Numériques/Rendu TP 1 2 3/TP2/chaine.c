#include <stdio.h>

int nombre_de_char(char tbl[], int taille, char c);

#define TAILLE 20

int main(int argc, char const *argv[])
{
    int mode = 0;

    char string[] = "Batiste"; // Taille du tableau calculée automatiquement

    // Calcul du nombre de caractere dans la string, sans '\0'
    int cpt = 0;
    for (int i = 0; string[i] != '\0'; i++)
        cpt++;
    int l_string = cpt;

    // Affichage de la string
    printf("Tableau : %s\n", string);

    // Calcule le nombre de fois qu'apparait un caractere dans la string

    printf("Entrer le char a rechercher dans le tableau : ");

    char ch;
    // fflush(stdin);
    scanf("%c", &ch);

    printf("Le charactere %c apparait %d fois dans la string [ %s ]", ch, nombre_de_char(string, l_string, ch), string);

    // Copie d'une chaine de caractere dans une autre

    char s1[100], s2[100], i;

    printf("\nEntrer la string 1 à copier : ");
    // fflush(stdin);
    while(getchar() != '\n');
    scanf("%s", s1);

    // On tourne dans le tableau donné jusqu'à trouver '\0'
    for (i = 0; s1[i] != '\0'; ++i) {
        // On copie chaque valeur de s1 dans s2
        s2[i] = s1[i];
    }

    // On ajoute le caractere de fin de chaine a la fin de s2
    s2[i] = '\0';

    printf("String s2 copiée : %s\n", s2);

    // Concatenation de deux chaines
    char t1[100], t2[100];

    printf("Entrer s1 à concatener : ");
    // fflush(stdin);
    while(getchar() != '\n');
    scanf("%s", t1);

    printf("Entrer s2 à concatener : ");
    // fflush(stdin);
    while(getchar() != '\n');
    scanf("%s", t2);

    // Concatenation

    int st1 = 0, st2 = 0, x, y;

    // Calcul des tailles de tableau
    for (int i = 0; t1[i] != '\0'; i++)
        st1++;
    for (int i = 0; t2[i] != '\0'; i++)
        st2++;

    // La taille de t3 est la somme des tailles de t1 et t2 et on ajoute un emplacement pour le caractere de fin de chaine
    char t3[st1 + st2 + 1];

    // On parcourt t1 et on copie chaque valeur dans t3
    for (x = 0; x < st1; x++)
    {
        t3[x] = t1[x];
    }

    // On parcourt t2 et on copie chaque valeur dans t3, en reprennant à la fin de t1
    for (y = 0; y < st2; y++, x++)
    {
        t3[x] = t2[y];
    }

    // On ajoute le caractere de fin de chaine a la fin de t3
    t3[x] = '\0';
    
    printf("\nt3 : %s\n", t3);

    return 0;
}

// Fonctions qui calcule le nombre de fois qu'un caractere "c" apparait dans une chaine "tbl" de taille "taille"
int nombre_de_char(char tbl[], int taille, char c)
{
    int cpt = 0;

    for (int i = 0; i < taille; i++)
    {
        if (tbl[i] == c)
        {
            cpt++;
        }
    }

    return cpt;
}
