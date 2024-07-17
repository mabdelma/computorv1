#include "computorv.h"

void write_char(char c) {
    write(1, &c, 1);
}

void write_str(const char *str) {
    while (*str) {
        write_char(*str);
        str++;
    }
}

void write_int(int n) {
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

    // Count number of digits
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }

    char *buffer = (char *)calloc(num_digits + 1, sizeof(char));
    if (buffer == NULL) {
        return; // Handle memory allocation failure
    }

    for (int i = num_digits - 1; i >= 0; i--) {
        buffer[i] = (n % 10) + '0';
        n /= 10;
    }

    write_str(buffer);
    free(buffer);
}

void write_double(double d, int precision) {
    // Handle negative numbers
    if (d < 0) {
        write_char('-');
        d = -d;
    }

    // Write the integer part
    int int_part = (int)d;
    write_int(int_part);

    // Write the decimal point
    write_char('.');

    // Write the fractional part
    double frac_part = d - int_part;
    for (int i = 0; i < precision; i++) {
        frac_part *= 10;
    }

    write_int((int)(frac_part + 0.5)); // Adding 0.5 for rounding
}