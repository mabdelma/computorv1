#include "computorv.h"

int ft_strlen(char *st)
{
    int i;

    i = 0;
    if(st == NULL)
        return(0);
    while(st[i])
    {
        if(i <= 500)
            i++;
        else
            return(-1);
    }
    return(i);
}

int ft_strpos(char letter, char *str)
{
    for(int j = 0; j < ft_strlen(str); j++)
    {
        if(str[j] == letter)
            return(j);
    }
    return(-1);
}

int ft_strlen_sin_WS(char *str)
{
    int i;

    i = 0;
    if(ft_strlen(str) == -1)
        return(-1);
    for(int j = 0; j < ft_strlen(str); j++)
    {
        if(!(str[j] == ' ' || str[j] == '\r' || str[j] == '\n'
            || str[j] == '\t' || str[j] == '\v' || str[j] == '\f'))
            i++;
    }
    return(i);   
}

unsigned int check_equal_zero(char *st)
{
    if(st == NULL)
        return(0);
    if(ft_strlen(st) == 2 && st[1] == '0')
    {
        printf("\nits zero\n");
        return(0);
    }
    return(1);
}

int count_signs(char *st)
{
    int count;

    count = 0;
    for(int i = 0; i < ft_strlen(st); i++)
    {
        if(st[i] == '-' || st[i] == '+')
            count++;
    }
    return(count);
}

unsigned int not_accepted_character(char *st)
{
    char c;
    int i;

    i = 0;
    while(st[i])
    {
        c = st[i];
        if(c >= 'a' && c <='z')
            i++;
        else if(c >= 'A' && c <= 'Z')
            i++;
        else if(c >= '0' && c <= '9')
            i++;
        else if (c == '.' || c == '*' || c == '^')
            i++;
        else if (c == '-' || c == '+')
            i++;
        else
            return(1);
    }
    return(0);
}

unsigned int not_accepted_format(char *st)
{
    char stage = 1;
    char point = 0;
    char found = 0;
    int i = 1;

    if(st[0] != '+' && st[0] != '-')
        return(32);
    while(st[i])
    {
        if(stage == 1)
        {
            if(st[i] == '*' && i > 1)
            {
                stage = 2;
                point = 0;
            }
            else if(!(st[i] >= '0' && st[i] <= '9') && !(st[i] == '.'))
                return(32);
            if(st[i] == '.')
            {
                if(point == 0)
                    point = 1;
                else
                    return(32);
            }
            if(i > 9)
            {
                printf("\nthhhh\n");
                return(544);
            }
        }
        else if(stage == 2)
        {
            if(st[i] >= 'a' && st[i] <= 'z')
                stage = 3;
            else if(st[i] >= 'A' && st[i] <= 'Z')
                stage = 3;
            else
                return(32);
        }
        else if(stage == 3)
        {
            if(st[i] == '^')
                stage = 4;
            else
                return(32);
        }
        else if(stage == 4)
        {
            if(!(st[i] >= '0' && st[i] <= '9'))
                return(32);
            else
                found = 1;
        }
        i++;
    }
    if((stage == 4 && found == 1) || stage == 1)
        return(0);
    else
        return(32);
}
unsigned int many_characters(char *st)
{
    char c;
    int i;

    c = 0;
    i = 0;
    while(st[i])
    {
        if((st[i] >= 'a' && st[i] <= 'z') || (st[i] >= 'A' && st[i] <= 'Z'))
        {
            if(!c)
                c = st[i];
            else if(c != st[i])
                return(64);
            else
                c = st[i];
        }
        i++;
    }
    return(0);
}
