#include <math.h>
#include <stdio.h>

int main()
{
    int a = 16, b = 3;

    // On affiche les différentes opérations possibles avec a et b
    printf("%i\n", a + b);
    printf("%i\n", a - b);
    printf("%i\n", a * b);
    printf("%i\n", a / b);
    printf("%i\n", a & b);
    printf("%i\n", a && b);
    printf("%i\n", a || b);
    printf("%i", !a);

    return 0;
}
