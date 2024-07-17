#include "computorv.h"

char *str_join(char *buf, char *add)
{
    char *newbuf;
    int len;

    if(buf == 0)
        len = 0;
    else
    len = strlen(buf);
    newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
    if(newbuf == 0)
        return(0);
    newbuf[0] = 0;
    if(buf != 0)
        strcat(newbuf, buf);
    free(buf);
    strcat(newbuf, add);
    return(newbuf);
}

char *ft_substring(char *str, int start, int end)
{
    char *nstr;
    int j;

    j = 0;
    if(!str)
    {
        return(NULL);
    }
    if(str[0] == 0)
    {
        return(NULL);
    }

    if(start >= ft_strlen(str) || start > end)
        return (NULL);
    if(end > ft_strlen(str))
        return(&str[start]);
    nstr = calloc(1, sizeof(*nstr) * (end - start + 2));
    if(!nstr)
        return(NULL);
    for(int i = start; i <= end; i++)
    {
        nstr[j++] = str[i];
    }
    nstr[j] = '\0';
    return(nstr);
}

char *str_sin_WS(char *str)
{
    char *nstr;
    int i;

    i = 0;
    if(!str)
        return(NULL);
    nstr = calloc(1,sizeof(*nstr) * (ft_strlen_sin_WS(str) + 1));
    if(!nstr)
        return(NULL);
    for(int j = 0; j < ft_strlen(str); j++)
    {
        if(!(str[j] == ' ' || str[j] == '\r' || str[j] == '\n'
            || str[j] == '\t' || str[j] == '\v' || str[j] == '\f'))
        {
            nstr[i++] = str[j];
        }       
    }
    nstr[i] = '\0';
    return(nstr);
}

char *ft_add_sign(char *st)
{
    char *str;
    int j;

    if(st)
    {
        if(!(st[0] == '+' || st[0] == '-'))
        {
            str = calloc(1, sizeof(*str) * (ft_strlen(st) + 2));
            str[0] = '+';
            j = 1;

        }
        else
        {
            //printf("\nftf\n");
            str = calloc(1, sizeof(*str) * (ft_strlen(st) + 1));
            j = 0;
        }
        for(int i = 0; i < ft_strlen(st); i++)
            str[i+j] = st[i];
        free(st);
    }
    else
    {
        str = st;
    }
    return(str);
}

char *move_to_left(char *left, char *right)
{
    char *str;
    int j;

    j = 0;
    if(check_equal_zero(right))
    {
        str = calloc(1,(sizeof(*str) * (ft_strlen(left) + ft_strlen(right) + 1)));
        j = ft_strlen(left);
        for(int i = 0; i < ft_strlen(right); i++)
        {
            if(right[i] == '+')
                str[j + i] = '-';
            else if(right[i] == '-')
                str[j + i] = '+';
            else
                str[j + i] = right[i];
        }
        for(int i = 0; i < ft_strlen(left); i++)
            str[i] = left[i];
        str[ft_strlen(left) + ft_strlen(right)] = '\0';
        free(right);
    }
    else
    {
        str = calloc(1,(sizeof(*str) * (ft_strlen(left) + 1)));
        j = ft_strlen(left);
        for(int i = 0; i < ft_strlen(left); i++)
            str[i] = left[i];
        str[ft_strlen(left)] = '\0';
        free(right);
    }
    return(str);
}
