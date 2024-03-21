#include "uart-zynq.h"

void _putchar(char c)
{
    uart_write_byte(UART1_BASE, c);
    // uart_write_byte(uart_id, (uint8_t) *string);
    // return c;
}