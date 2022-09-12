/*
Exercice 2 - L’appel à fork() dans une boucle : Ecrire un programme qui fait appel à la fonction fork() dans une 
boucle for (k=0 ; k<3 ; k++). 
A chaque itération le programme affichera les informations suivantes : 
 (k = valeur de k) : je suis le processus : pid, mon pere est : ppid , retour : retour 
où 
• pid est le PID du processus courant, 
• ppid est le PID du processus père du processus courant,
• retour est la valeur du code retour de l'appel à la fonction fork().
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int id;

	for(int k = 0; k<3; k++)
	{
		id = fork();
		printf("k = %d: process %d\t| pere : %d\t| retour : %d\n", k, getpid(), getppid(), id);
	}

	return 0;
}
