#include "computorv.h"

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
