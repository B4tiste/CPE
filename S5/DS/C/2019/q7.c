#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int nbr[argc - 1];

    int i;

    for(i = 1; i < argc; i++)
    {
        nbr[i] = atoi(argv[i]);
    }

    for (i = 0; i < argc; i++)
    {
        printf("%d %d\n", i, nbr[i]);
    }
    
    

    return 0;
}
