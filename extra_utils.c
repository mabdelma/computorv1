#include "computorv.h"

void print_errors(unsigned int errorflg)
{
    printf("you got these errors: -\n");
    if(errorflg & 1)
        printf(" -using many consecutives (+,-) signs\n");
    if(errorflg & 2)
        printf(" -using many consecutives power signs\n");
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
    if(errorflg & 265)
        printf(" -entering more than 500 characters (maximum allowed 500 characters)\n");
    if(errorflg & 512)
        printf(" -entering more big number (maximum allowed number of 8 digits including the . sign)\n");
    if(errorflg & 1024)
        printf(" -entering some consecutive zeros or a starting zero number\n");
}

double get_nonzero_coef(t_parameter *t)
{
    t_parameter *par;
    double catchflg = 0.0;

    par = t;
    while(par)
    {
        if(par->coef != 0.0)
            catchflg = par->coef;
        par = par->prev;
    }
    return(catchflg);
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

void parameters_handler(char *str)
{
    t_parameter *parameter1;
    char catchflg = 0;
    
    parameter1 = fill_parameters(str);
    write_str("move all to the left-hand side: ");
    put_equation(parameter1, 1);
    catchflg = get_nonzero_coef(parameter1);
    reduced_list(parameter1);
    write_str("common factors grouping: ");
    put_equation(parameter1, 0);
    reorder_parameters(parameter1);
    write_str("Reduced Form: ");
    put_equation(parameter1, 0);
    reduced_parameters(parameter1);
    printf("polynomial degree: %s\n", get_highest_power(parameter1));
    solve_equation(parameter1, catchflg);
    free_all_parameters(parameter1);
}