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
            if (*s == 'd') {
                int d = va_arg(args, int);
                putc('0' + d, addr);
            }
            size--;
        } else {
            putc(*s, addr);
        }
        s++;
    }
}
