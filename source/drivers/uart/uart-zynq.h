/*
 *  UART-ZYNQ.C
 *
 *  Simple UART driver for Zynq platform
 *
 *  2017.05.21 Created
 *
 */

#ifndef _UART_ZYNQ_H
#define _UART_ZYNQ_H

#include <stdbool.h>
#include <stdint.h>

typedef enum uart_id
{
    UART1_ID = 0,
    UART2_ID,
    UART_ID_NUM,
} uart_id_t;

// chardev_t *get_uart_dev(uart_id_t uart_id);

void    uart_init(uart_id_t uart_id);
uint8_t uart_read_byte(uart_id_t uart_id);
void    uart_write_byte(uart_id_t uart_id, uint8_t ch);
void    uart_write_bytes(uart_id_t uart_id, uint8_t *string);

#endif /* _UART_ZYNQ_H */