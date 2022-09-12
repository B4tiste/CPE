#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    for(int i = 1; i<argc; i++)
    {
        if(!fork())
        {
            printf("a\n");
            char *path = strcat("/src/", strcat(argv[i], ".out"));
            printf("%s\n", path);
            execlp("gcc", "gcc", argv[i], "-o", path, NULL);
        }
        else
        {
            exit(0);
        }
    }

    printf("Done\n");

    return 0;
}