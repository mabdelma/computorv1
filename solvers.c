#include "computorv.h"

void solve_first_order(t_parameter *t)
{
    double coef;
    double result;
    t_parameter *par;

    par = t;
    while(par)
    {
        if(par->power == 1)
            coef = par->coef;
        else if(par->power == 0)
            result = par->coef;
        par = par->prev;
    }
    write_str("x = -1 * ");
    write_double(result, 2);
    write_str(" / ");
    write_double(coef, 2);
    result = (-1 * result) / coef;
    write_str("\nx = ");
    write_double(result, 2);
    write_str("\n");
}

double calculate_sigma(t_parameter *t)
{
    t_parameter *par;
    double a = 0;
    double b = 0;
    double c = 0;
    double sigma;

    par = t;
    
    while(par)
    {
        if(par->power == 1)
            b = par->coef;
        else if(par->power == 0)
            c = par->coef;
        else if(par->power == 2)
            a = par->coef;
        par = par->prev;
    }
    write_str("a = ");
    write_double(a, 2);
    write_str(", b = ");
    write_double(b, 2);
    write_str(", c = ");
    write_double(c, 2);
    write_str("\nsigma = (b ^ 2) - (4 * a * c) = ");
    sigma = (b * b) - (4 * a * c);
    write_double(sigma, 2);
    write_str("\n");
    return(sigma);
}

void solve_second_order(t_parameter *t, double sigma)
{
    t_parameter *par;
    double b;
    double a;
    double sol;
    double tem = 0.0;

    a = 0.0;
    b = 0.0;
    sol = 0.0;
    par = t;
    while(par)
    {
        if(par->power == 1)
            b = par->coef;
        else if(par->power == 2)
            a = par->coef;
        par = par->prev;
    }
    sol = (-1 * b) / (2 * a);
    if(sigma > 0)
    {
        tem = sol - (sqrt(sigma) / (2 * a));
        write_str("x = (-b - sqrt(sigma)) / (2 * a) = ");
        write_double(tem, 2);
        write_str("\nx = (-b + sqrt(sigma)) / (2 * a) = ");
        tem = sol + (sqrt(sigma) / (2 * a));
        write_double(tem, 2);
        write_str("\n");
    }
    else if(sigma == 0)
    {
        write_str("x = (-b) / (2 * a) = ");
        write_double(sol, 2);
        write_str("\n");
    }
    else
    {
        tem = sqrt((-1 * sigma)) / (2 * a);
        if(tem < 0.0)
            tem *= -1.0;
        write_str("x = (-b + sqrt(sigma)) / (2 * a) = ");
        write_double(sol, 2);
        write_str(" + ");
        write_double(tem, 2);
        write_str("i\nx = (-b - sqrt(sigma)) / (2 * a) = ");
        write_double(sol, 2);
        write_str(" - ");
        write_double(tem, 2);
        write_str("i\n");
        //printf("%f + %fi\n%f - %fi\n", sol, temp, sol, temp);
    }
    a = tem;

}
