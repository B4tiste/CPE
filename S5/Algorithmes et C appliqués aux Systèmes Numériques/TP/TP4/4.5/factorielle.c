#include <stdio.h>
#include <math.h>

int factorielle(int num);

int main(int argc, char const *argv[])
{

    int n;

    printf("Entrer un nombre : ");
    fflush(stdin);
    scanf("%d", &n);

    printf("%d", factorielle(n));  


    return 0;
}

int factorielle(int num)
{
    if (num == 0)
    {
        return 1;
    }
    else
    {
        return num * factorielle(num - 1);
    }
}