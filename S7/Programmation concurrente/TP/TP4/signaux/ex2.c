#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    /*
        Ecrire un programme qui rélaise un affichage dans un boucle infinie, mais qui prévoit de s'arrêter à la réception
        d'un signal SIGINT (Ctrl+C).
    */

    int i = 0;

    signal(SIGINT, SIG_IGN); // Redirectio du signal SIGINT sur un signal IGNORE

    while(1)
    {
        printf("i = %d \n", i);
        i++;
    }

    return 0;
}

