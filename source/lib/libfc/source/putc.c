#include "uartps.h"

void _putchar(char c)
{
    uart_write_byte(UART1_ID, c);
}
