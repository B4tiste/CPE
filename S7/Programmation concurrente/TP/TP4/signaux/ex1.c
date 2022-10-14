#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

// signal handler function 
void sigint_handler(int sig_num);

int main(int argc, char const *argv[])
{
    /*
        Ecrire un programme qui rélaise un affichage dans un boucle infinie, mais qui prévoit de s'arrêter à la réception
        d'un signal SIGINT (Ctrl+C).
    */

    int i = 0;

    signal(SIGINT, sigint_handler); // Redirection du signal SIGINT sur le pointeur de fonction sigint_handler

    while(1)
    {
        printf("i = %d \n", i);
        i++;
    }

    return 0;
}

void sigint_handler(int sig_num)
{
    if (SIGINT == sig_num)
    {
        printf("SIGINT reçu, fermeture du programme \n");
        exit(0);
    }
}
