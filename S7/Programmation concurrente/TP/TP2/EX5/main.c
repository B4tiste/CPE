#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char tblProg[argc][10];

    // For de chaque fichier c donné en parametre
    for (int i = 1; i<argc; i++)
    {
        printf("Prog %d : %s\n", i, argv[i]);

        // créer un fork sur chaque fhcier donné en parametre
        if (!fork())
        {
            char *token = strtok(argv[i], ".");
            printf("Compilation de : %s, %s \n", argv[i], token);

            char *nomFichier = 

            execlp("gcc", "gcc", strcat(argv[i], ".c"), "-o", token, NULL);
            printf("argv:%s, token:%s\n", argv[i], token);  
        }
    }

    printf("Done\n");

    return 0;
}