#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int pfd[2];
    int pid;

    pipe(pfd);
    pid = fork();

    if (pid == 0)
    {
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        execlp("wc", "wc", "-m", NULL);
    }
    else
    {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);
        execlp("cat", "cat", "main.c", NULL);
    }
    
    return 0;
}