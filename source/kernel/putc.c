#include "stdio.h"

void putc(char c, uart_t *addr)
{
    *addr = c;
}
