#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    // Successivement
    system("ls");
    system("who");
    system("ps");

    
    // Simultanement
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