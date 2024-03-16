#include "stdio.h"

void kputc(char c, uart_t *addr)
{
    *addr = c;
}
