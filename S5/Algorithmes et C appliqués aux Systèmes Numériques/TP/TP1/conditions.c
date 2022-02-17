#include <stdio.h>

int main(int argc, char const *argv[])
{
    // On verifie les conditions
    for (int i = 0; i <= 1000; i++)
    {
        if ((i % 2 == 0) && (i % 15 == 0))
        {
            printf("%i\n", i);
        }
        else if ((i % 103 == 0) || (i % 107 == 0))
        {
            printf("%i\n", i);
        }
        else if((i%7 == 0 || i%5 == 0) && (i%3 != 0))
        {
            printf("%i\n", i);
        }
    }

    return 0;
}
