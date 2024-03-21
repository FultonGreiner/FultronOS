#include "uart-zynq.h"

void putc(char c)
{
    uart_write_byte(UART1_ID, c);
}
