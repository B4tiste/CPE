#include <stdio.h>

// structure etudiant : 
typedef struct etudiant {
    char nom[20];
    char prenom[20];
    char adresse[30];
    float noteC;
    float noteOS;
} etudiant;

int main(int argc, char const *argv[])
{
    // creation d'un tableau de 5 etudiants
    struct etudiant etudiants[5];

    // remplissage du tableau d'etudiants
    for (int i = 0; i < 5; i++)
    {
        printf("Etudiant %d\n", i+1);
        printf("Nom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].nom);
        printf("Prenom : ");
        fflush(stdin);
        scanf("%s", etudiants[i].prenom);
        printf("Adresse : ");
        fflush(stdin);
        scanf("%s", etudiants[i].adresse);
        printf("Note C : ");
        // fflush(stdin);
        while(getchar() != '\n');
        scanf("%f", &etudiants[i].noteC);
        printf("Note OS : ");
        // fflush(stdin);
        while(getchar() != '\n');
        scanf("%f", &etudiants[i].noteOS);
    }

    // afficher les informations de chaque etudiant
    for (int i = 0; i < 5; i++)
    {
        printf("Etudiant %d\n", i+1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prenom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note C : %f\n", etudiants[i].noteC);
        printf("Note OS : %f\n", etudiants[i].noteOS);
    }

    return 0;
}
