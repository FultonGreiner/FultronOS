#include "stdio.h"

#include <stdarg.h>
// #include <stdio.h>
#include <stdint.h>
#include <string.h>

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

void kprintf(const char *s, uart_t *addr, ...)
{
    int size = count_args(s);
    va_list args;
    va_start(args, addr);

    while ( *s != '\0' ) {
        if ( (*s == '%') ) {
            s++;
            switch (*s) {
                case 'd': {
                    int d = va_arg(args, int);
                    kputc('0' + d, addr);
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *);
                    while (*str != '\0') {
                        kputc(*str, addr);
                        str++;
                    }
                    break;
                }
                case 'c': {
                    int c = va_arg(args, int);
                    kputc(c, addr);
                    break;
                }
                case 'f': {
                    double f = va_arg(args, double);
                    int f_int = (int) f;
                    kputc('0' + f_int, addr);
                    break;
                }
            }
            size--;
        } else {
            kputc(*s, addr);
        }
        s++;
    }
}
