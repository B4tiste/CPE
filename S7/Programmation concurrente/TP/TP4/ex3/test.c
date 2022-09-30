#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <memory.h>
#include <fcntl.h>
#include <time.h>

#define N 10

int main()
{
    int etat, nbPair[2], nbImpair[2], sommePair[2], sommeImpair[2];
    int i, nombre;
    char buffer[256];

    srand(time(NULL));

    if (!fork())
    {
        printf("Générateur \n");
        close(nbPair[0]);
        close(nbImpair[0]);

        for (i = 0; i < N; i++)
        {
            nombre = rand() % 100;
            if (nombre % 2)
            {
                write(nbPair[1], nombre, sizeof(int));
            }
            else
            {
                write(nbImpair[1], nombre, sizeof(int));
            }
        }
        write(nbPair[1], -1, sizeof(int));
        write(nbImpair[1], -1, sizeof(int));

        close(nbPair[1]);
        close(nbImpair[1]);

        /*Filtre pair*/
        if (!fork())
        {
            printf("FiltrePair\n");

            exit(0);
        }

        /*Filtre impair*/
        if (!fork())
        {
            printf("FiltreImpair\n");

            exit(0);
        }

        while (wait(&etat) != -1)
            ;

        read(nbPair[0], buffer, 5);
        read(nbImpair[0], buffer, 5);

        exit(0);
    }

    return 0;
}