#include "../include/stdio.h"

#include <stdint.h>
#include <stdarg.h>

void printf(const char *s, ...);

int count_args(const char *s)
{
    int count = 0;
    while (*s != '\0') {
        if (*s == '%' && *(s - 1) != '\\') {
            s++;
            count++;
        }
        s++;
    }
    return count;
}

void printf(const char *s, ...)
{
    int size = count_args(s);

    va_list args;
    va_start(args, s);

    while ( *s != '\0' ) {
        if ( (*s == '%') ) {
            s++;
            switch (*s) {
                case 'd': {
                    int d = va_arg(args, int);
                    putc('0' + d, stdout);
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *);
                    while (*str != '\0') {
                        putc(*str, stdout);
                        str++;
                    }
                    break;
                }
                case 'c': {
                    int c = va_arg(args, int);
                    putc(c, stdout);
                    break;
                }
                case 'f': {
                    double f = va_arg(args, double);
                    int f_int = (int) f;
                    putc('0' + f_int, stdout);
                    break;
                }
            }
            size--;
        } else {
            putc(*s, stdout);
        }
        s++;
    }
}
