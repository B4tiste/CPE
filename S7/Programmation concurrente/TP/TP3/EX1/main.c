#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fils1, fils2, n, m, tube[2];

    char buffer[256];

    char *message = "Batiste";
    int tailleMessage = strlen(message);

    // Création du pipe avec pour extrémitées les deux cases de tube[]
    if (pipe(tube) != 0) 
    {
        perror("Problème - création du tube\n");
        exit(1);
    }

    fils1 = fork();

    if (fils1 == 0)
    {
        close(tube[0]);
        printf("Je suis le fils producteur\n");
        printf("Je dépose 5 caractères dans le pipe\n");
        write(tube[1], message, tailleMessage);

        close(tube[1]);
        exit(3);
    }
    else
    {
        fils2 = fork();
        if (fils2 == 0)
        {
            printf("Je suis le fils consommateur\n");
            close(tube[1]);
            read(tube[0], buffer, tailleMessage);
            printf("Caractères lus dans le pipe : %s\n", buffer);
            exit(3);
        }
        else
        {
            printf("Le processus père se termine\n");
            close(tube[0]);
        }
    }
    
    return 0;
}