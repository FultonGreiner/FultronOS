#include <string.h>

// #include <printf.h>

#include "printf.h"
#include "uart-zynq.h"

#define RX_BUFFER_SIZE 100
static char rx_buffer[RX_BUFFER_SIZE] = {0};
size_t rx_buffer_index = 0;

#define STATUS_BUFFER_SIZE 100
static char status_buffer[STATUS_BUFFER_SIZE] = {0};

#define CARRIAGE_RETURN (0xDUL)
#define BACKSPACE       (0x8UL)
#define NEWLINE         (0xAUL)

#define KERNEL_PROMPT   ("> ")

int main(void)
{
    char ch[6] = "R:  ";
    float f = 3.14159;
    uart_initialise();

    printf("\nHello, world!\r\n");

    while (1)
    {
        memset((void*)rx_buffer, 0, RX_BUFFER_SIZE);
        memset((void*)status_buffer, 0, STATUS_BUFFER_SIZE);

        printf(KERNEL_PROMPT);

        char c = 0;
        rx_buffer_index = 0;

        int i = 0;
        do
        {
            rx_buffer[i] = read_uart_char(UART1_BASE);
            write_uart_char(UART1_BASE, rx_buffer[i]);
        } while ( CARRIAGE_RETURN != rx_buffer[i++] );

        printf("\r\n");
    }

    return 0;
}
