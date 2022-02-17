#include <math.h>
#include <stdbool.h>
#include "operator.h"

// somme, différence, produit, quotient, modulo, 'et', ou et négation

// fonction somme
// somme de deux entiers
int somme(int a, int b)
{
    return a + b;
}

// fonction soustraction
// soustraction de deux entiers
int soustraction(int a, int b)
{
    return a - b;
}

// fonction multiplication
// multiplication de deux entiers
int multiplication(int a, int b)
{
    return a * b;
}

// fonction division
// division de deux entiers
int division(int a, int b)
{
    return a / b;
}

// fonction modulo
// modulo de deux entiers
int modulo(int a, int b)
{
    return a % b;
}

// fonction et
// et de deux entiers
int et(int a, int b)
{
    return a & b;
}

// fonction ou
// ou de deux entiers
int ou(int a, int b)
{
    return a | b;
}

// fonction negation
// negation d'un entier
int negation(int a)
{
    return ~a;
}

