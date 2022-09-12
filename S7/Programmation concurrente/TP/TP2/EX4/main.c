#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(!fork())
    {
        if(!fork())
        {
            execlp("ls", "ls", "-l", NULL);
        }
        execlp("ps", "ps", NULL);
    }
    execlp("who", "who", NULL);

    return 0;
}