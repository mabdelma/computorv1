#include "computorv.h"

char ft_isint(char st)
{
    if(st >= '0' && st <= '9')
        return(1);
    return(0);
}

double get_highest_coef(t_parameter *t)
{
    double coef = 0;
    t_parameter *par;

    if(t)
        coef = t->coef;
    else
        return(0);
    par = t->prev;
    if(par)
    {
        while(par)
        {
            if(par->coef > coef)
                coef = par->coef;
            par = par->prev;
        }
    }
    return(coef);
}

unsigned int get_paramters_count(t_parameter *t)
{
    unsigned int count = 0;
    t_parameter *par;

    par = t;
    while(par)
    {
        count++;
        par = par->prev;
    }
    return(count);
}

double get_lowest_coef(t_parameter *t)
{
    double coef = 0;
    t_parameter *par;

    if(t)
        coef = t->coef;
    else
        return(0);
    par = t->prev;
    if(par)
    {
        while(par)
        {
            if(par->coef < coef)
                coef = par->coef;
            par = par->prev;
        }
    }
    return(coef);
}

char *get_highest_power(t_parameter *t)
{
    char *pow;
    t_parameter *par;

    if(!t)
        return(NULL);
    pow = t->power;
    par = t->prev;
    while(par)
    {
        if(strcmp(par->power, pow) > 0 && par->coef != 0.0)
            pow = par->power;
        par = par->prev;
    }
    return(pow);
}

char *get_lowest_power(t_parameter *t)
{
    char *pow;
    t_parameter *par;

    if(!t)
        return(NULL);
    pow = t->power;
    par = t->prev;
    while(par)
    {
        if(strcmp(par->power, pow) < 0 && par->coef != 0.0)
            pow = par->power;
        par = par->prev;
    }
    return(pow);
}

double ft_strtodouble(char *st)
{
    double x;
    double y;
    int end;
    int point;

    x = 0.0;
    y = 1.0;
    end  = 0;
    point = ft_strpos('.', st);
    if(st[0] == '+' || st[0] == '-')
        end = 1;
    for(int i = ft_strlen(st) - 1; i >= end; i--)
    {
        if(st[i] == '.')
            continue;
        else
        {
            x += (st[i] - '0') * y;
            y *= 10.0;
        }
        
    }
    if(point != -1)
    {
        y = 1.0;
        for(int i = ft_strlen(st) - 1; i > point; i--)
            y *= 0.1;
        x *= y;
    }
    if(st[0] == '-')
        x *= -1.0;
    return (x);
}
