#include <stdio.h>

int main()
{
	//Affichage valeur int
	printf("Taille d'un entier : %ld\n", sizeof(int));
	printf("Taille d'un entier* : %ld\n", sizeof(int*));
	printf("Taille d'un entier** : %ld\n", sizeof(int**));

	//Affichage valeur char
	printf("Taille d'un caractere* : %ld\n", sizeof(char*));
	printf("Taille d'un caractere** : %ld\n", sizeof(char**));
	printf("Taille d'un caractere*** : %ld\n", sizeof(char***));

	//Affichage valeur float
	printf("Taille d'un float* : %ld\n", sizeof(float*));
	printf("Taille d'un float** : %ld\n", sizeof(float**));
	printf("Taille d'un float*** : %ld\n", sizeof(float***));
}
