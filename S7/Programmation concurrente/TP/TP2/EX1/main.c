#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(!fork())
    {
        execlp("gcc", "gcc", "test.c", "-o", "test.out", NULL);
    }
    execlp("ls", "ls", "-al", NULL);

    return 0;
}