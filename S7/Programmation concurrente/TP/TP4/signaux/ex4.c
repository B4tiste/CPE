#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // signal(SIGINT, sigint_handler); // Redirection du signal SIGINT sur le pointeur de fonction sigint_handler

    int pid = fork();

    // Processus fils qui fait un affichage dans une boucle infinie
    if(!pid)
    {
        int i = 0;
        while(1)
        {
            printf("Je suis le processus fils \n");
            // sleep(1);
        }
    }
    // Processus père qui fait un affichage dans une boucle for
    // Et qui envoie un signal SIGKILL au fils à la 3e itération
    else
    {
        for(int i = 0; i < 3; i++)
        {
            printf("Je suis le processus père \n");
            sleep(1);
        }

        kill(pid, SIGKILL);
    }

    return 0;
}

