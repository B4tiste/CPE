#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void sigint_handler(int sig_num);

int main(int argc, char const *argv[])
{
    // signal(SIGINT, sigint_handler); // Redirection du signal SIGINT sur le pointeur de fonction sigint_handler

    int pid = fork();

    // Processus fils qui fait un affichage dans une boucle infinie
    if(!pid)
    {
        signal(SIGINT, sigint_handler); 

        int i = 0;
        while(1)
        {
            printf("Je suis le processus fils \n");
            sleep(1);
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
    }

    return 0;
}

void sigint_handler(int sig_num)
{
    if (SIGINT == sig_num)
    {
        printf("SIGINT reçu, fermeture du programme \n");
    }
}
