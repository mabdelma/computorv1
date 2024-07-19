#ifndef COMPUTORV_H
#define COMPUTORV_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_equation{
    char *left;
    char *right;
}   t_equation;


typedef struct s_parameter{
    struct s_parameter *prev;
    struct s_parameter *next;
    double  coef;
    char *power;
    char *str;
}   t_parameter;


int ft_strlen(char *st);
char ft_isint(char st);
char *str_join(char *buf, char *add);
char *ft_substring(char *str, int start, int end);
int ft_strpos(char letter, char *str);
int ft_strlen_sin_WS(char *str);
char *str_sin_WS(char *str);
unsigned int errors(char *eq);
double ft_strtodouble(char *st);
char *ft_add_sign(char *st);
unsigned int check_equal_zero(char *st);
char *move_to_left(char *left, char *right);
int count_signs(char *st);
void fill_coef_pow(char *st, t_parameter *t);
t_parameter *fill_parameters(char *st);
char *get_highest_power(t_parameter *t);
char *get_lowest_power(t_parameter *t);
double get_highest_coef(t_parameter *t);
double get_lowest_coef(t_parameter *t);
void free_parameter(t_parameter *t);
void free_all_parameters(t_parameter *t);
void reduced_list(t_parameter *t);
void reduced_parameters(t_parameter *t);
void reorder_parameters(t_parameter *t);
void put_equation(t_parameter *t, char status);
void solve_first_order(t_parameter *t);
double calculate_sigma(t_parameter *t);
void solve_second_order(t_parameter *t, double sigma);
unsigned int not_accepted_character(char *st);
unsigned int not_accepted_format(char *st);
unsigned int not_accepted_numbers(char *st);
unsigned int    many_characters(char *st);
unsigned int   error_level3(char *st);
unsigned int   error_level2(char *st);
unsigned int error_core(char *av);
void write_char(char c);
void write_str(const char *str);
void write_int(int n);
void write_double(double d, int precision);
void print_errors(unsigned int errorflg);
double sqrt_newton(double number);
void solve_equation(t_parameter *t);
void parameters_handler(char *str);

#endif