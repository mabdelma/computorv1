#include "computorv.h"

void write_char(char c)
{
    write(1, &c, 1);
}

void write_str(const char *str)
{
    while (*str) {
        write_char(*str);
        str++;
    }
}

void write_int(int n)
{
    if (n == 0) {
        write_char('0');
        return;
    }
    if (n < 0) {
        write_char('-');
        n = -n;
    }
    int num_digits = 0;
    int temp = n;
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }
    char *buffer = (char *)calloc(num_digits + 1, sizeof(char));
    if (buffer == NULL) {
        return;
    }
    for (int i = num_digits - 1; i >= 0; i--) {
        buffer[i] = (n % 10) + '0';
        n /= 10;
    }
    write_str(buffer);
    free(buffer);
}

void write_double(double d, int precision)
{
    if (d < 0) {
        write_char('-');
        d = -d;
    }
    int int_part = (int)d;
    write_int(int_part);
    write_char('.');
    double frac_part = d - int_part;
    for (int i = 0; i < precision; i++) {
        frac_part *= 10;
        if(frac_part < 1)
            write_char('0');
    }
    
    write_int((int)(frac_part + 0.5));
}