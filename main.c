#include "computorv.h"

int main(int ac, char **av)
{
    char *str;
    t_equation equation1 = {0};
    unsigned int errorflg = 0;

    if(ac != 2)
    {
        printf("wrong number of arguments.\nplease enter the full equation after program name like this \"equation \"\n");
        exit(1);
    }
    errorflg = error_core(av[1]);
    if(!errorflg)
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
        print_errors(errorflg);
        if(errorflg & 231)
        {
            if(str)
                free(str);
        }
    }
    else
    {
        parameters_handler(str);
        if(str)
            free(str);
    }
    return(0);
}
