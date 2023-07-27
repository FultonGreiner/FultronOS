#include "../include/stdio.h"

#include <stdint.h>
#include <stdarg.h>

int count_args(const char *s) {
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



void printf(const char *s, uart_t *addr, ...) {
    int size = count_args(s);

    va_list args;
    va_start(args, addr);

    while ( *s != '\0' ) {
        if ( (*s == '%') ) {
            s++;
            switch (*s) {
                case 'd': {
                    int d = va_arg(args, int);
                    putc('0' + d, addr);
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *);
                    while (*str != '\0') {
                        putc(*str, addr);
                        str++;
                    }
                    break;
                }
                case 'c': {
                    int c = va_arg(args, int);
                    putc(c, addr);
                    break;
                }
                case 'f': {
                    double f = va_arg(args, double);
                    int f_int = (int) f;
                    putc('0' + f_int, addr);
                    break;
                }
            }
            size--;
        } else {
            putc(*s, addr);
        }
        s++;
    }
}
