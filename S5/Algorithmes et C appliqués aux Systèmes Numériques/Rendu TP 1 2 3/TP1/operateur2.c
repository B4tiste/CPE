#include <math.h>
#include <stdio.h>

// +, -, *, /, %, &, |

int main(int argc, char const *argv[])
{
    int a, b;
    char op;
    long int resultat;

    // On demande à l'utilisateur de saisir a et b

    printf("Entrer la valeur de num1 : ");
    // fflush(stdin);
    scanf("%i", &a);

    printf("\nEntrer la valeur de num1 : ");
    while(getchar() != '\n');
    scanf("%i", &b);

    while (1)
    {

        printf("Entrer l'operateur choisis entre [+, -, *, /, %%, &, |] : ");
        // fflush(stdin);
        while(getchar()!='\n'); //Clear le \n du précédent scanf
        scanf("%c", &op);

        // En fonction de l'opérateur choisi, on effectue l'opération correspondante
        switch (op)
        {
        case '+':
            // printf("%i", a + b);
            resultat = a + b;
            break;

        case '-':
            // printf("%i", a - b);
            resultat = a - b;
            break;

        case '*':
            // printf("%i", a * b);
            resultat = a * b;
            break;

        case '/':
            // printf("%i", a / b);
            resultat = a / b;
            break;

        case '%':
            // printf("%i", a % b);
            resultat = a % b;
            break;

        case '&':
            // printf("%i", a & b:);
            resultat = a & b;
            break;

        case '|':
            // printf("%i", a | b);
            resultat = a | b;
            break;

        default:
            printf("\nOperateur non disponible !\n");
            break;
        }

        printf("Le resultat de %i %c %i est : %ld \n\n", a, op, b, resultat);
    }

    return 0;
}
