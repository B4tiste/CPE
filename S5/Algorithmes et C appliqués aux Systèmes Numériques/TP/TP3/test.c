#include <stdio.h>
#include <string.h>

int main ()
{
	int Compteur[10] = {0} ;
	int i=0,j=0,k=0;
	struct couleur
	{
		int rouge;
		int vert;
		int bleu;
		int alpha;
	};

	struct couleur tab_RGBA[10];

	printf("Veuillez saisir les couleurs RGBA espacées : \n");

	while(scanf("%x %x %x %x",&tab_RGBA[i].rouge,&tab_RGBA[i].vert,&tab_RGBA[i].bleu,&tab_RGBA[i].alpha) == 4 || (i==10))
	{
		if(i>0)
		{
		// On va parcourir le tableau actuel
			for(j=(i-1);j>=0;j--)
			{
				// On va tester pour voir si les valeurs sont identiques ou non
				if(tab_RGBA[i].rouge == tab_RGBA[j].rouge && tab_RGBA[i].vert == tab_RGBA[j].vert && tab_RGBA[i].bleu == tab_RGBA[j].bleu && tab_RGBA[i].alpha == tab_RGBA[j].alpha)
				{
					Compteur[j]++;
					// On va remplacer la ligne actuelle
					i--;
				}
			}
		}
	  i++;
	}

	printf("FIN de la saisie \n");

	// On va afficher les valeurs
	for(k=0;k<i;k++)
	{
		 printf("%d 0x%2.2hhx 0x%2.2hhx 0x%2.2hhx 0x%2.2hhx \n", Compteur[k]+1, tab_RGBA[k].rouge, tab_RGBA[k].vert, tab_RGBA[k].bleu, tab_RGBA[k].alpha);
	}

	  return 0;
}

