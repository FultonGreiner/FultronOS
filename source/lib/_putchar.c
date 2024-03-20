#include "uart-zynq.h"

void _putchar(char c)
{
    write_uart_char(UART1_BASE, c);
    // write_uart_char(uart_id, (unsigned char) *string);
    // return c;
}