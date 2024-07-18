#include "computorv.h"

void print_errors(char errorflg)
{
    printf("you got these errors: -\n");
    if(errorflg & 1)
        printf(" -using many consucatives (+,-) signs\n");
    if(errorflg & 2)
        printf(" -using many consucatives power signs\n");
    if(errorflg & 4)
        printf(" -not using only one equal sign\n");
    if(errorflg & 8)  
        printf(" -using invalid equation format\n");
    if(errorflg & 16)
        printf(" -using an inacceptable character\n");
    if(errorflg & 32)
        printf(" -using an inacceptable format\n");
    if(errorflg & 64)
        printf(" -using multiple variables format\n");
    if(errorflg & 128)
        printf(" -using invalid equation format\n");
}

double sqrt_newton(double number)
{
    if (number < 0)
        return -1;
    if (number == 0 || number == 1)
        return number;
    double precision = 0.000001;
    double guess = number > 1 ? number : 1;
    double next_guess = 0.5 * (guess + number / guess);
    while (guess - next_guess > precision || next_guess - guess > precision)
    {
        guess = next_guess;
        next_guess = 0.5 * (guess + number / guess);
    }
    return next_guess;
}