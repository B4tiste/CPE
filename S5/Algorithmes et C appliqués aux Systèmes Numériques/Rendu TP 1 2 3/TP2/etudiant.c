#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Creation d'un tablea à 3 dimensions
    char tab_etu[5][5][30];

    int i, j;

    // [Nom] [Prenom] [Adresse] [note1] [note2]

    // Remplissage du tableau par l'utilisateur
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            switch (j)
            {
            case 0:
                printf("Nom de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 1:
                printf("Prenom de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 2:
                printf("Adresse de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 3:
                printf("Note 1 de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            case 4:
                printf("Note 2 de l'etu %i : ", i + 1);
                fflush(stdin);
                scanf("%s", &tab_etu[i][j]);
                break;

            default:
                break;

            }
        }

        printf("\n");
    }

    int x, y;

    // Affichage du tableau
    for (x = 0; x < 5; x++)
    {
        for (y = 0; y < 5; y++)
        {
            printf("%s ", tab_etu[x][y]);
        }

        printf("\n");
    }

    return 0;
}
