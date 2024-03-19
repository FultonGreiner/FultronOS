#include "stdio.h"

#include <stdarg.h>
#include <stdint.h>

#include "serial.h"

int count_args(const char *s)
{
    int count = 0;
    while (*s != '\0') {
        if (*s == '%' && *(s - 1) != '\\')
        {
            s++;
            count++;
        }
        s++;
    }
    return count;
}

void kprintf(const char *s, ...)
{
    int size = count_args(s);
    va_list args;
    va_start(args, s);

    while ( *s != '\0' )
    {
        if ( (*s == '%') )
        {
            s++;
            switch (*s)
            {
                case 'd':
                {
                    int d = va_arg(args, int);
                    _putchar('0' + d);
                    break;
                }
                case 's':
                {
                    char *str = va_arg(args, char *);
                    while (*str != '\0')
                    {
                        _putchar(*str);
                        str++;
                    }
                    break;
                }
                case 'c':
                {
                    int c = va_arg(args, int);
                    _putchar(c);
                    break;
                }
                case 'f':
                {
                    double f = va_arg(args, double);
                    int f_int = (int) f;
                    _putchar('0' + f_int);
                    _putchar('.');

                    for (int i = 0; i < 1; i++)
                    {
                        f_int = (int) (f * 10) - (f_int * 10);
                        _putchar('0' + f_int);
                    }
                    break;
                }
            }
            size--;
        }
        else
        {
            _putchar(*s);
        }
        s++;
    }
}
