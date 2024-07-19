#include "computorv.h"

unsigned int errors(char *eq)
{
    unsigned int error;
    char found;
    char c;
    int i;

    found = 0;
    error = 0;
    c = 0;
    i = 0;
    if(!eq)
        return(0x80);
    while(eq[i])
    {
        if(eq[i + 1] && (eq[i + 1] == '-' || eq[i + 1] == '+'))
            if(eq[i] == '-' || eq[i] == '+')
                error += 1;
        if(eq[i + 1] && eq[i + 1] == '^' && eq[i] == '^')
            error += 2;
        if(eq[i] == '=')
        {
            if(found == 0)
                found = 1;
            else
                error += 4;
        }
        if((eq[i] >= 'a' && eq[i] <= 'z') || (eq[i] >= 'A' && eq[i] <= 'Z'))
        {
            if(!c)
                c = eq[i];
            else if(c != eq[i])
                error +=64;
            else
                c = eq[i];
        }
        i++;
    }
    if(eq[i-1] == '=')
        error += 128;
    if(!found)
        error += 4;
    return (error);
}

unsigned int error_level3(char *st)
{
    unsigned int errorflg = 0;

    if(not_accepted_character(st))
        errorflg |= 16;
    if(not_accepted_format(st))
        errorflg |= 32;

    return(errorflg);    
}

unsigned int error_level2(char *st)
{
    char *str;
    int current;
    unsigned int errorflg = 0;


    current = 0;
    for(int i = 0; i < count_signs(st); i++)
    {
        for(int j = current + 1; j <= ft_strlen(st); j++)
        {
            if(st[j] == '-' || st[j] == '+' || !st[j] || st[j] == '=')
            {
                str =  ft_substring(st, current, j - 1);
                //printf("parameter: %s\n",str);
                errorflg |= error_level3(str);
                free(str);
                current = j;
                break;
            }
        } 
    }
    return (errorflg);
}