#include <string.h>

// #include "disk.h"
#include "fultronfs.h"
#include "printf.h"
#include "uartps.h"

#define RX_BUFFER_SIZE 100
static char rx_buffer[RX_BUFFER_SIZE] = {0};
size_t rx_buffer_index = 0;

#define STATUS_BUFFER_SIZE 100
static char status_buffer[STATUS_BUFFER_SIZE] = {0};

#define CARRIAGE_RETURN (0xDUL)
#define BACKSPACE       (0x8UL)
#define NEWLINE         (0xAUL)

#define KERNEL_PROMPT   ("> ")

static char flash_tx_buffer[RX_BUFFER_SIZE] = "TEST FLASH";
static char flash_rx_buffer[RX_BUFFER_SIZE] = {0};

int main(void)
{
    uart_init(UART1_ID);

    printf("\nHello, world!\r\n\n");

    Disk *disk = get_sdram_disk();
    FileSystem *fs = get_sdram_fs();
    fs->debug(disk);

    // while (1)
    // {
    //     memset((void*)rx_buffer, 0, RX_BUFFER_SIZE);
    //     memset((void*)status_buffer, 0, STATUS_BUFFER_SIZE);

    //     printf(KERNEL_PROMPT);

    //     char c = 0;
    //     rx_buffer_index = 0;

    //     int i = 0;
    //     do
    //     {
    //         rx_buffer[i] = uart_read_byte(UART1_ID);
    //         uart_write_byte(UART1_ID, rx_buffer[i]);
    //     } while ( CARRIAGE_RETURN != rx_buffer[i++] );

    //     printf("\r\n");
    // }

    return 0;
}