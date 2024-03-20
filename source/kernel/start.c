/*
 *  uart-zynq-main.c
 *
 *  Simple test for uart-zynq driver
 *
 *  2017.05.23 Created
 *
 */

#include <string.h>

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

#define RX_BUFFER_SIZE 100
static char rx_buffer[RX_BUFFER_SIZE] = {0};
size_t rx_buffer_index = 0;

#define STATUS_BUFFER_SIZE 100
static char status_buffer[STATUS_BUFFER_SIZE] = {0};

#define CARRIAGE_RETURN (0xDUL)
#define BACKSPACE       (0x8UL)

int main()
{
    char ch[6] = "R:  ";
    float f = 3.14159;
    uart_initialise();

    printf("Hello, world!\r\n");

    while (1)
    {
        /*
        * Read the character, and then
        * print out with formatter.
        */

        memset((void*)rx_buffer, 0, RX_BUFFER_SIZE);
        memset((void*)status_buffer, 0, STATUS_BUFFER_SIZE);

        printf("\r\n> ");

        char c = 0;
        rx_buffer_index = 0;

        int i = 0;
        do
        {
            rx_buffer[i] = read_uart_char(UART1_BASE);
            // if ( BACKSPACE == rx_buffer[i] )
            // {
            //     printf("BACKSPACE\n\r");
            // }
            write_uart_char(UART1_BASE, rx_buffer[i]);
            i++;
        } while ( CARRIAGE_RETURN != rx_buffer[i++] );
    }

    return 0;
}
