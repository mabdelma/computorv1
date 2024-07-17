#include "computorv.h"

int main(int ac, char **av)
{
    char *str;
    t_equation equation1 = {0};
    t_parameter *parameter1;
    double sigma;
    char errorflg = 0;

    if(ac != 2)
    {
        printf("wrong number of arguments.\nplease enter the full equation after program name like this \"equation \"\n");
        exit(1);
    }
    if(!av[1])
        errorflg = 8;
    else if(ft_strlen_sin_WS(av[1])==0)
        errorflg = 8;
    else
    {
        printf("your entery: %s\n", av[1]);
        str = str_sin_WS(av[1]);
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
        
        if(errorflg & 228)
        {
            if(str)
                free(str);
        }
    }

    else
    {
        parameter1 = fill_parameters(str);
        write_str("move all to the left-hand side: ");
        put_equation(parameter1, 1);
        reduced_list(parameter1);
        write_str("common factors grouping: ");
        put_equation(parameter1, 0);
        reorder_parameters(parameter1);
        write_str("Reduced Form: ");
        put_equation(parameter1, 0);
        printf("polynomial degree: %d\n", (int)get_highest_power(parameter1));
        if(get_highest_power(parameter1) == 1)
            solve_first_order(parameter1);
        else if(get_highest_power(parameter1) == 2)
        {
            sigma = calculate_sigma(parameter1);
            if(sigma > 0)
                printf("discriminant is strictly positive, the two solutions are:\n");
            if(sigma < 0)
                printf("discriminant is strictly negative, the two solutions are:\n");
            else if(sigma == 0)
                printf("discriminant is zero, the solution is:\n");
            solve_second_order(parameter1, sigma);
        }
        else if(get_highest_power(parameter1) > 2)
        {
            printf("the polynomial degree is strictly greater than 2, i can't solve.\n");
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