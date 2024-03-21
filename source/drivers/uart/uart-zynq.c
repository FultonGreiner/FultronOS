/*
 *  uart-zynq.c
 *
 *  Bare Metal UART driver for Xilinx Zynq devices
 *
 *  2017.05.21 Created
 *
 */

#include "uart-zynq.h"

#include <stdint.h>

static unsigned int default_uart_id;
static struct XUARTPS *UART1 = (struct XUARTPS*) UART1_BASE;
static struct XUARTPS *UART2 = (struct XUARTPS*) UART2_BASE;

static struct XUARTPS *uart_interfaces[UART_ID_NUM] =
{
    [UART1_ID] = (struct XUARTPS*) UART1_BASE,
    [UART2_ID] = (struct XUARTPS*) UART2_BASE,
};

/*---------------------------------------------------------------------------
** Entry conditions:    None.
**
** Exit conditions:     Both UARTs are configured correctly.
**
** Purpose:             Call the functions to configure the Zynq UARTs
**                      simultaneously.
**
** Parameters:          Void.
**
** Returns:             Void.
**
** Notes:               None.
*/
void uart_init(uart_id_t uart_id)
{
    struct XUARTPS *uart = uart_interfaces[uart_id];

    /* Disable UART */
    uart->Control_reg0 = 0;

    /* 115200 8N1 */
    uart->Baud_rate_divider_reg0 = XUARTPS_BDIV_CD_115200;
    uart->Baud_rate_gen_reg0 = XUARTPS_BRGR_CD_115200;
    uart->mode_reg0 = XUARTPS_MR_PAR_NONE;
    
    /* Enable UART */
    uart->Control_reg0 =  (XUARTPS_CR_TXEN | XUARTPS_CR_RXEN | XUARTPS_CR_TXRES | XUARTPS_CR_RXRES);
    
    return;
}

/*---------------------------------------------------------------------------
** Entry conditions:    None.
**
** Exit conditions:     A character is read from the UART.
**
** Purpose:             Blocking read of a character from the specified UART.
**
** Parameters:          uart_id - The UART to use.
**
** Returns:             The character read from the UART.
**
** Notes:               This function is blocking and will wait until a
**                      character is available to read.
*/
uint8_t uart_read_byte(uart_id_t uart_id)
{
    struct XUARTPS *uart = uart_interfaces[uart_id];

    while( ( (uart->Channel_sts_reg0) & UART_STS_RXEMPTY) > 0);

    return (uint8_t)(uart->TX_RX_FIFO0);
}

/*---------------------------------------------------------------------------
** Entry conditions:    A character is supplied to be written.
**
** Exit conditions:     The supplied character has been wrote to the UART.
**
** Purpose:             Blocking write of a character to the specified UART.
**
** Parameters:          uart_id - The UART to use.
**                      ch      - The character to write.
**
** Returns:             Void.
**
** Notes:               This function is blocking and will wait until the
**                      transmit buffer has space for a character.
*/
void uart_write_byte(uart_id_t uart_id, uint8_t ch)
{
    struct XUARTPS *uart = uart_interfaces[uart_id];

    while( ( (uart->Channel_sts_reg0) & UART_STS_TXFULL) > 0);

    uart->TX_RX_FIFO0 = (uint32_t)(ch); /* Transmit char */
}

/*---------------------------------------------------------------------------
** Entry conditions:    None.
**
** Exit conditions:     The supplied string has been wrote to the UART.
**
** Purpose:             Write of a string to the specified UART.
**
** Parameters:          uart_id - The UART to use.
**                      string  - A pointer to the beginning of null-terminated
**                                string to write.
**
** Returns:             Void.
**
** Notes:               This function may or may not be blocking based on the
**                      end function used to write the character.
**                      The string must be null-terminated (\0).
*/
void uart_write_bytes(unsigned int uart_id, const char *string)
{
    while (*string != '\0')
    {
        uart_write_byte(uart_id, (uint8_t) *string);
        string++;
    }
}