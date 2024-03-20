/*
 *  uart-zynq-main.c
 *
 *  Simple test for uart-zynq driver
 *
 *  2017.05.23 Created
 *
 */

#include "printf.h"
#include "uart-zynq.h"

/*---------------------------------------------------------------------------
** Entry conditions:    None.
**
** Exit conditions:     None.
**
** Purpose:             Entry point to the application.
**
** Parameters:          Void.
**
** Returns:             Void.
**
** Notes:
*/

int main()
{
    char ch[6] = "R:  ";
    float f = 3.14159;
    uart_initialise();

    printf("HERE!\r\n");

    printf("UART1_BASE: 0x%x\r\n", UART1_BASE);
    printf("UART2_BASE: 0x%x\r\n", UART2_BASE);
    printf("Float test: %0.5f\r\n", f);

    while (1)
    {
        /*
        * Read the character, and then
        * print out with formatter.
        */

        ch[3] = read_uart_char(UART1_BASE);
        write_uart_string(UART1_BASE, ch);
        write_uart_char(UART1_BASE, '\n');
        write_uart_char(UART1_BASE, '\r');
    }

    return 0;
}
