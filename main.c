#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct s_equation{
    char *left;
    char *right;
}   t_equation;


typedef struct s_parameter{
    struct s_parameter *prev;
    struct s_parameter *next;
    double  coef;
    double power;
    char *str;
}   t_parameter;


int ft_strlen(char *st)
{
    int i;

    i = 0;
    if(st == NULL)
        return(0);
    while(st[i])
        i++;
    return(i);
}

char ft_isint(char st)
{
    if(st >= '0' && st <= '9')
        return(1);
    return(0);
}

char *ft_substring(char *str, int start, int end)
{
    char *nstr;
    int j;

    j = 0;
    if(start >= ft_strlen(str) || start > end)
        return (NULL);
    if(end > ft_strlen(str))
        return(&str[start]);
    nstr = malloc(sizeof(*nstr) * (end - start + 2));
    if(!nstr)
        return(NULL);
    for(int i = start; i <= end; i++)
    {
        nstr[j++] = str[i];
    }
    nstr[j] = '\0';
    return(nstr);
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
    for(int j = 0; j < ft_strlen(str); j++)
    {
        if(!(str[j] == ' ' || str[j] == '\r' || str[j] == '\n'
            || str[j] == '\t' || str[j] == '\v' || str[j] == '\f'))
            i++;
    }
    return(i);   
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

char errors(char *eq)
{
    char error;
    char found;
    char c;
    int i;

    found = 0;
    error = 0;
    c = 0;
    i = 0;
    if(!eq)
        return(128);
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
            y *= .1;
        x *= y;
    }
    if(st[0] == '-')
        x *= -1.0;
    return (x);
}

char *ft_add_sign(char *st)
{
    char *str;

    if(st && ft_isint(st[0]))
    {
        str = calloc(1, sizeof(*str) * (ft_strlen(st) + 2));
        str[0] = '+';
        for(int i = 0; i < ft_strlen(st); i++)
            str[i+1] = st[i];
        free(st);
    }
    else
    {
        str = st;
    }
    return(str);
}

char check_equal_zero(char *st)
{
    if(st == NULL)
        return(-1);
    if(ft_strlen(st) == 1 && st[0] == '0')
        return(0);
    return(1);
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
        return(str);
    }
    return(left);
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

void fill_coef_pow(char *st, t_parameter *t)
{
    char *str;

    if(ft_strpos('*', st) == -1)
    {
        str = st;
        t->coef = ft_strtodouble(str);
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
        temp = (t_parameter *)malloc(sizeof(t_parameter));
        temp->prev = temp1;
        if(temp1)
            temp->prev->next = temp;
        for(int j = current + 1; j <= ft_strlen(st); j++)
        {
            if(st[j] == '-' || st[j] == '+' || !st[j])
            {
                temp->str =  ft_substring(st, current, j - 1);
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
double get_highest_power(t_parameter *t)
{
    double pow;
    t_parameter *par;

    pow = 0;
    par = t;
    if(par && !par->next)
    {
        while(par)
        {
            if(par->power > pow)
                pow = par->power;
            par = par->prev;
        }
    }
    else if(par && !par->prev)
    {
        while(par)
        {
            if(par->power > pow)
                pow = par->power;
            par = par->next;
        }
    }
    return(pow);
}

double get_lowest_power(t_parameter *t)
{
    double pow;
    t_parameter *par;

    pow = get_highest_power(t);
    par = t;
    if(par && !par->next)
    {
        while(par)
        {
            if(par->power < pow)
                pow = par->power;
            par = par->prev;
        }
    }
    else if(par && !par->prev)
    {
        while(par)
        {
            if(par->power < pow)
                pow = par->power;
            par = par->next;
        }
    }
    return(pow);
}

void free_parameter(t_parameter *t)
{
    if(!t)
        return ;
    if(t->str)
        free(t->str);
    free(t);
    
}
void free_all_parameters(t_parameter *t)
{

    t_parameter *par;
    t_parameter *par2;
    

    par = t;
    while(par)
    {
        par2 = par->prev;
        free_parameter(par);
        par = par2;
    }
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

    par = t;
    temp = t;
    while(par)
    {
        if(par->coef == 0.0)
        {
            //printf("fount coef:%f, power:%f\n", par->coef, par->power);
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
                    break;
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
            }
        }
        par = par->prev;        
    }
    return(temp);
}

void put_equation(t_parameter *t)
{
    t_parameter *par;
    double coef;

    par = t;
    if(par && !par->next)
    {
        while(par)
        {
            coef = par->coef;
            if(par->coef >= 0)
            {
                if(par != t)
                    printf("+ ");
            }
            else
            {
                printf("- ");
                coef *= -1;
            }
            printf("%.1f * x ^ %d ", coef, (int)par->power);
            //printf("current address: %p ,nextaddress: %p ,prevaddress: %p\n", par, par->next,par->prev);
            par = par->prev;
        }
    }
    printf(" = 0\n");
}

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
    result = (-1 * result) / coef;
    printf("%f\n", result);
}

double calculate_sigma(t_parameter *t)
{
    t_parameter *par;
    double a;
    double b;
    double c;
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
    sigma = (b * b) - (4 * a * c);
    return(sigma);
}

void solve_second_order(t_parameter *t, double sigma)
{
    t_parameter *par;
    double b;
    double a;
    double sol;
    double temp;

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
        temp = sol - (sqrt(sigma) / (2 * a));
        printf("%f\n", temp);
        temp = sol + (sqrt(sigma) / (2 * a));
        printf("%f\n", temp);
    }
    else if(sigma == 0)
    {
        printf("%f\n", sol);
    }
    else
    {
        temp = sqrt((-1 * sigma)) / (2 * a);
        printf("%f + %fi\n%f - %fi\n", sol, temp, sol, temp);
    }

}

char not_accepted_character(char *st)
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

char not_accepted_format(char *st)
{
    char stage = 1;
    char found = 0;
    int i = 1;

    if(st[0] != '+' && st[0] != '-')
        return(32);
    while(st[i])
    {
        if(stage == 1)
        {
            if(st[i] == '*')
                stage = 2;
            else if(!(st[i] >= '0' && st[i] <= '9') && !(st[i] == '.'))
                return(32);
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
            if(!(st[i] >= '0' && st[i] <= '9') && !(st[i] == '.'))
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
char    many_characters(char *st)
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

char    error_level3(char *st)
{
    char errorflg = 0;

    if(not_accepted_character(st))
        errorflg += 16;
    if(not_accepted_format(st))
        errorflg += 32;

    return(errorflg);    
}
char    error_level2(char *st)
{
    char *str;
    int current;
    char errorflg = 0;


    current = 0;
    for(int i = 0; i < count_signs(st); i++)
    {
        for(int j = current + 1; j <= ft_strlen(st); j++)
        {
            if(st[j] == '-' || st[j] == '+' || !st[j] || st[j] == '=')
            {
                str =  ft_substring(st, current, j - 1);
                errorflg |= error_level3(str);
                free(str);
                current = j;
                break;
            }
        } 
    }
    return (errorflg);
}

int main(int ac, char **av)
{
    char *str;
    t_equation equation1 = {0};
    t_parameter *parameter1;
    double sigma;
    char errorflg = 0;

    equation1.left = NULL;
    equation1.right = NULL;
    if(ac != 2)
    {
        printf("Wrong number of arguments.\nPlease enter the full equation after program name like this \"equation \"\n");
        exit(1);
    }
    if(av[1])
        errorflg = 128;
    else if(ft_strlen_sin_WS(av[1])==0)
        errorflg = 128;
    else
    {
        str = str_sin_WS(av[1]);
        printf("your entery: %s\n", str);
        errorflg |= errors(str);
    }
    
    if(!errorflg)
    {
        equation1.left = ft_add_sign(ft_substring(str, 0, ft_strpos('=', str) - 1));
        equation1.right = ft_add_sign(ft_substring(str, ft_strpos('=', str) + 1, ft_strlen(str)));
        free(str);
        str = move_to_left(equation1.left,equation1.right);
        if(equation1.left)
            free(equation1.left);
        errorflg |= error_level2(str);
    }

    if(errorflg)
    {
        printf("You got these errors: -\n");
        if(errorflg & 1)
            printf(" -using many consucatives (+,-) signs\n");
        if(errorflg & 2)
            printf(" -using many consucatives power signs\n");
        if(errorflg & 4)
            printf(" -Not using only one equal sign\n");
        if(errorflg & 8)
            printf(" -not adding any signs \n");
        if(errorflg & 16)
            printf(" -using an inacceptable character\n");
        if(errorflg & 32)
            printf(" -using an inacceptable format\n");
        if(errorflg & 64)
            printf(" -using multiple variables format\n");
        if(errorflg & 128)
            printf(" -using invalid equation format\n");
    }
    else
    {
        parameter1 = fill_parameters(str);
        reduced_list(parameter1);
        reorder_parameters(parameter1);
        parameter1 = remove_zero_parameters(parameter1);
        printf("Polynomial degree: %d\n", (int)get_highest_power(parameter1));
        if(get_highest_power(parameter1) == 1)
            solve_first_order(parameter1);
        else if(get_highest_power(parameter1) == 2)
        {
            sigma = calculate_sigma(parameter1);
            if(sigma > 0)
                printf("Discriminant is strictly positive, the two solutions are:\n");
            if(sigma < 0)
                printf("Discriminant is strictly negative, the two solutions are:\n");
            else if(sigma == 0)
                printf("Discriminant is zero, the solution is:\n");
            solve_second_order(parameter1, sigma);
        }
        else if(get_highest_power(parameter1) > 2)
        {
            printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
        }
        else
        {
            printf("there isn't any equation for me to solve.\n");
        }
        free_all_parameters(parameter1);
        if(str)
            free(str);
    }
    
    return(0);
}