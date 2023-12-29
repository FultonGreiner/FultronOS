#include "../inc/stdio.h"

#include <stdint.h>
#include <stdarg.h>

stdout_t *stdout = (stdout_t*) STDOUT_BASE;

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

int count_digits(int n)
{
    int r = 0;
    while (n > 0)
    {
        n /= 10;
        r++;
    }
    return r;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* citoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    while (num != 0)
    {
        int rem = num % base;
        // str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        str[i++] = rem + '0';
        num = num / base;
    }
 
    if (isNegative)
    {
        str[i++] = '-';
    }
 
    str[i] = '\0';
 
    reverse(str, i);
 
    return str;
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
                    int digits = count_digits(d);

                    char d_str[digits + 2]; /* additional space for null terminator & (-) sign */
                    citoa(d, d_str, 10);
                    int i = 0;
                    while (d_str[i] != '\0')
                    {
                        putc(d_str[i], stdout);
                        i++;
                    }
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *);
                    while (*str != '\0')
                    {
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
