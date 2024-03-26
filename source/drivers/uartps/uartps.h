#ifndef _UARTPS_H
#define _UARTPS_H

#include <stdint.h>

typedef enum uart_id
{
    UART1_ID = 0,
    UART2_ID,
    UART_ID_NUM,
} uart_id_t;

void    uart_init(uart_id_t uart_id);
uint8_t uart_read_byte(uart_id_t uart_id);
void    uart_write_byte(uart_id_t uart_id, uint8_t ch);
void    uart_write_bytes(uart_id_t uart_id, uint8_t *string);

#endif /* _UARTPS_H */