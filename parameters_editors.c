#include "computorv.h"

void fill_coef_pow(char *st, t_parameter *t)
{
    char *str;

    if(!st)
    {
        printf("\nf2\n");
        t->coef = 0.0;
        t->power = 0.0;
        return ;
    }

    if(ft_strpos('*', st) == -1)
    {
        str = st;
        if(str)
        {
            if(strlen(str) == 1 &&(str[0] == '-' || str[0] == '+'))
            {
                printf("\nf2\n");
                t->coef = 0.0;
            }
            else
                t->coef = ft_strtodouble(str);
        }
        else
        {
            t->coef = 0.0;
        }
        t->power = 0.0;
    }
    else
    {
        str = ft_substring(st, 0, ft_strpos('*', st) - 1);
        t->coef = ft_strtodouble(str);
        free(str);
        str = ft_substring(st, ft_strpos('^', st) + 1, ft_strlen(st));
        t->power = ft_strtodouble(str);
        free(str);
    }
}

t_parameter *fill_parameters(char *st)
{
    int current;
    t_parameter *temp;
    t_parameter *temp1;

    temp1 = NULL;
    current = 0;
    for(int i = 0; i < count_signs(st); i++)
    {
        temp = calloc(1, sizeof(t_parameter));
        temp->prev = temp1;
        if(temp1)
            temp->prev->next = temp;
        for(int j = current + 1; j <= ft_strlen(st); j++)
        {
            if(st[j] == '-' || st[j] == '+' || !st[j])
            {
                temp->str =  ft_substring(st, current, j - 1);
                //printf("\ntemp: %s, %ld\n",temp->str, strlen(temp->str));
                fill_coef_pow(temp->str, temp);
                current = j;
                break;
            }
        }
        temp->next = NULL;
        temp1 = temp;
    }
    return(temp);
}

void reduced_list(t_parameter *t)
{
    t_parameter *par;
    t_parameter *temp;
    t_parameter *par2;

    par = t;
    if(par && !par->next)
    {
        while(par)
        {
            if(!par->prev)
                break;
            par2 = par->prev;
            while(par2)
            {
                if(par->power == par2->power)
                {
                    par->coef += par2->coef;
                    if(par2->prev)
                    {
                        par2->next->prev = par2->prev;
                        par2->prev->next = par2->next;
                    }
                    else
                    {
                        par2->next->prev = NULL;
                    }
                    temp = par2;
                    par2 = par2->prev;
                    free_parameter(temp);
                    continue;
                }
                par2 = par2->prev;
            }
            par = par->prev;
        }
    }
}

void reorder_parameters(t_parameter *t)
{
    t_parameter *par;
    t_parameter temp;
    t_parameter *par2;

    par = t;
    while(par)
    {
        if(par->prev)
        {
            par2 = par->prev;
            while(par2)
            {
                if(par->power > par2->power)
                {
                    temp.coef = par->coef;
                    temp.power = par->power;
                    par->coef = par2->coef;
                    par->power = par2->power;
                    par2->coef = temp.coef;
                    par2->power = temp.power;
                }
                par2 = par2->prev;
            } 
        }
        par = par->prev;
    }
}

t_parameter *remove_zero_parameters(t_parameter *t)
{
    t_parameter *par;
    t_parameter *temp;
    t_parameter *tofree;

    par = t;
    temp = t;
    while(par)
    {
        if(par->coef == 0.0)
        {
            tofree = par;
            if(par->next)
            {
                if(par->prev)
                    {
                        par->next->prev = par->prev;
                        par->prev->next = par->next;
                    }
                else
                {
                    par->next->prev = NULL;
                    printf("\n parameteradd %p, coef: %f, power: %f\n", tofree, tofree->coef, tofree->power);
                    free_parameter(tofree);
                    break ;
                }
            }
            else
            {
                if(par->prev)
                {
                    par->prev->next = NULL;
                    temp = par->prev;
                }
                else
                {
                    temp = NULL;
                }
                
                par = tofree->prev;
            }
            printf("\n parameteradd %p, coef: %f, power: %f\n", tofree, tofree->coef, tofree->power);
            free_parameter(tofree);
            continue;
        }
        // if(par->coef == 0.0)
        // {
        //     tofree = par;
        //     printf("\nfount coef:%f, power:%f\n", tofree->coef, tofree->power);
        //     if(par->next)
        //     {
        //         if(par->prev)
        //             {
        //                 par->next->prev = par->prev;
        //                 par->prev->next = par->next;
        //             }
        //         else
        //         {
        //             par->next->prev = NULL;
        //             printf("\n to %s\n", tofree->str);
        //             free_parameter(tofree);
        //             break;
        //         }
        //     }
        //     else
        //     {
        //         if(par->prev)
        //         {
        //             par->prev->next = NULL;
        //             temp = par->prev;
        //         }
        //         else
        //         {
        //             temp = NULL;
        //         }
        //     }
        //     par = tofree->prev;
        //     printf("\n to2 %s\n", tofree->str);
        //     printf("\nfree address: %p\n", tofree);
        //     free_parameter(tofree);
        //     continue;
        // }
        par = par->prev;        
    }
    return(temp);
}

void put_equation(t_parameter *t, char status)
{
    t_parameter *par;
    double coef;
    int printed = 0;

    coef = (double) status;
    par = t;
    if(par && !par->next)
    {
        while(par)
        {
            coef = par->coef;
            if(par->coef > 0)
            {
                if(par != t)
                    write_str(" + ");
            }
            else if(par->coef < 0)
            {
                write_str(" - ");
                coef *= -1;
            }
            if(par->coef == 0 && !status);
            else
            {
                if(par->coef == 0)
                    write_str(" + ");    
                write_double(coef, 1);
                write_str(" * x ^ ");
                write_int((int)par->power);
                printed++;
            }
            
            par = par->prev;
        }
    }
    if(printed == 0)
        write_str("0");
    write_str(" = 0\n");
}
