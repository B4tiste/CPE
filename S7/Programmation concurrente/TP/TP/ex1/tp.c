// Exercice 1 

#include <stdio.h>

int main(int argc, char *argv[]) 
{
	int i;
	printf("Nom du programme : %s\n", argv[0]);
	printf("Nombre d'arguments de la ligne de commande : %d\n", argc-1);
	printf("Les arguments sont : \n");
	for(i=1; i<argc; i++)
	{
		printf("\t%d : %s\n", i, argv[i]);
	}

	return 0;
}
