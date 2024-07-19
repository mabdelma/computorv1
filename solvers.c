#include "computorv.h"

void solve_first_order(t_parameter *t)
{
    double coef;
    double result;
    t_parameter *par;

    par = t;
    while(par)
    {
        if(strcmp(par->power, "1") == 0)
            coef = par->coef;
        else if(strcmp(par->power, "0") == 0)
            result = par->coef;
        par = par->prev;
    }
    write_str("x = -1 * ");
    write_double(result, 4);
    write_str(" / ");
    write_double(coef, 9);
    result = (-1 * result) / coef;
    write_str("\nx = ");
    write_double(result, 4);
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
        if(strcmp(par->power, "1") == 0)
            b = par->coef;
        else if(strcmp(par->power, "0") == 0)
            c = par->coef;
        else if(strcmp(par->power, "2") == 0)
            a = par->coef;
        par = par->prev;
    }
    write_str("a = ");
    write_double(a, 4);
    write_str(", b = ");
    write_double(b, 4);
    write_str(", c = ");
    write_double(c, 4);
    write_str("\nsigma = (b ^ 2) - (4 * a * c) = ");
    sigma = (b * b) - (4 * a * c);
    write_double(sigma, 4);
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
        if(strcmp(par->power, "1") == 0)
            b = par->coef;
        else if(strcmp(par->power, "2") == 0)
            a = par->coef;
        par = par->prev;
    }
    sol = (-1 * b) / (2 * a);
    if(sigma > 0)
    {
        tem = sol - (sqrt_newton(sigma) / (2 * a));
        write_str("x = (-b - sqrt_newton(sigma)) / (2 * a) = ");
        write_double(tem, 4);
        write_str("\nx = (-b + sqrt_newton(sigma)) / (2 * a) = ");
        tem = sol + (sqrt_newton(sigma) / (2 * a));
        write_double(tem, 4);
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
        tem = sqrt_newton((-1 * sigma)) / (2 * a);
        if(tem < 0.0)
            tem *= -1.0;
        write_str("x = (-b + sqrt_newton(sigma)) / (2 * a) = ");
        write_double(sol, 2);
        write_str(" + ");
        write_double(tem, 2);
        write_str("i\nx = (-b - sqrt_newton(sigma)) / (2 * a) = ");
        write_double(sol, 2);
        write_str(" - ");
        write_double(tem, 2);
        write_str("i\n");
        //printf("%f + %fi\n%f - %fi\n", sol, temp, sol, temp);
    }
    a = tem;

}

void solve_equation(t_parameter *t, double catchflg)
{
    double sigma = 0.0;

    if(strcmp(get_highest_power(t), "1") == 0)
            solve_first_order(t);
    else if(strcmp(get_highest_power(t), "2") == 0)
    {
        sigma = calculate_sigma(t);
        if(sigma > 0)
            printf("discriminant is strictly positive, the two solutions are:\n");
        if(sigma < 0)
            printf("discriminant is strictly negative, the two solutions are:\n");
        else if(sigma == 0)
            printf("discriminant is zero, the solution is:\n");
        solve_second_order(t, sigma);
    }
    else if(strcmp(get_highest_power(t), "2") > 0 || ft_strlen(get_highest_power(t)) > 1)
        {
            printf("the polynomial degree is strictly greater than 2, I can't solve.\n");
        }
    else
    {
        if(catchflg != 0.0 && t->coef == 0.0)
            printf("each real number is a solution...\n");
        else
            printf("there isn't any equation for me to solve.\n");
    }
}