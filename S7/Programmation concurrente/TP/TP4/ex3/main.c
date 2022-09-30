#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define QUANTITE 10

// Fonction d'aléatoire
void srand(unsigned int seed);
int hasard(int a, int b);

int main()
{
	// Init random seed
	srand((unsigned int)time(0));

	// Création processus
	int filtrePair = fork();

	// Création des tubes
	int tubePair[2], tubeImpair[2], sommePair[2], sommeImpair[2];

	// Si on est dans le filtrePair
	if (filtrePair == 0)
	{
		
	}
	else
	{
		int filtreImpair = fork();

		// Si on est dans le filtreImpair
		if (filtreImpair == 0)
		{
			
		}
		else
		{
			// On est dans le main
			// On génère dix nombres alétoires
			for(int i = 0; i < QUANTITE; i++)
			{
				int rdmNbr = hasard(0, 10);

				// Si il est impair
				if(rdmNbr%2)
				{
					
				}
				// Si il est pair
				else
				{
					
				}
			}
		}
	}
	
	return 0;
}

int hasard(int a, int b)
{
	return a + rand()%(b - a + 1);
}
