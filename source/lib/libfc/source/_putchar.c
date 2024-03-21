#include "uart-zynq.h"

void _putchar(char c)
{
    uart_write_byte(UART1_BASE, c);
    // uart_write_byte(uart_id, (unsigned char) *string);
    // return c;
}