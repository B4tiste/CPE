#include <stdio.h>

int main(int argc, char const *argv[])
{

    // Liste de types : short, int, long int, float, double et long double
    
    short _short = 0x1234;
    int _int = 0x12345678;
    long int _lint = 0x12345678;
    float _float = 0x12345678;
    double _double = 0x1234567812345678;
    long double _ldouble = 0x00000000001234512345;

    // printf("taille long double : %d\n", sizeof(long double));

    char *ptr = &_short;

    // n = 0x1234
    // print 

    for (int i = sizeof(_short) - 1; i >= 0; i--)
    {
        printf("%02x ", *(ptr + i));
    }

    printf("\n\n");

    *ptr = &_ldouble;

    for(int i = sizeof(_ldouble); i > 0; i--)
    {
        printf("%02x ", *(ptr + i));
    }
    

    return 0;
}
