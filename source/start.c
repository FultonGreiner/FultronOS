#include <string.h>

#include "printf.h"
#include "uartps.h"

#include "ff.h"
// #include "sdram.h"

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

static FATFS fs;

int main(void)
{
    MKFS_PARM fmt_opt = {0};

    fmt_opt.fmt = FM_ANY;

    uart_init(UART1_ID);

    printf("\nHello, world!\r\n\n");

    // mount the default drive
    FRESULT res = f_mount(&fs, "/", 0);
    if ( FR_OK != res )
    {
        printf("f_mount() failed, res = %d\r\n", res);
        return -2;
    }

    res = f_mkfs("/", &fmt_opt, (void*)NULL, 1);
    if ( FR_OK != res )
    {
        printf("f_mkfs() failed, res = %d\r\n", res);
        return -3;
    }

    printf("Opened file system.\r\n");

    FIL file;
    res = f_open(&file, "/test.txt", FA_WRITE | FA_OPEN_ALWAYS);
    if ( FR_OK != res )
    {
        printf("f_open() failed, res = 0x%x\r\n", res);
        return -4;
    }

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