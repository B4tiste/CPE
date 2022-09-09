#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Nbr de note < 1 
    if(argc == 1)
    {
        printf("Aucune moyenne à calculer\n");
        exit(0);
    }
    // On vérifie que les notes [0; 20]
    else
    {
        for(int i = 0; i<=argc-1; i++)
        {
            float note = atof(argv[i]);
            if ((note < 0) || (note > 20))
            {
                printf("Note non valide\n");
                exit(0);
            }
        }
    }
    
    int nbrNotes = argc-1;
    int moyenne = 0;

    for(int i = 0; i<nbrNotes; i++)
    {
        moyenne += atof(argv[i+1]);
    }

    printf("La moyenne est de : %.2d\n", moyenne/nbrNotes);

    return 0;
}