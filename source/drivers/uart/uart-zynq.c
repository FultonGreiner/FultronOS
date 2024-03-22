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

/*
 * Section 19.2.3 Baud Rate Generator
 *
 * The baud rate can be calculated using the following equation:
 * baud rate = sel_clk / CD * (BDIV + 1)
 */

#define XUARTPS_BRGR_CD_115200  62
#define XUARTPS_BDIV_CD_115200   6

/*
 * Appendix B.33 UART Controller (UART)
 */

#define UART1_BASE 0xe0000000
#define UART2_BASE 0xe0001000

/*
 * CR (0x00000000)
 */
#define XUARTPS_CR_STOPBRK (1<<8)       /* STPBRK (STOPBRK)      */
#define XUARTPS_CR_STTBRK  (1<<7)       /* STTBRK (STARTBRK)     */
#define XUARTPS_CR_RSTTO   (1<<6)       /* RSTTO  (TORST)        */
#define XUARTPS_CR_TXDIS   (1<<5)       /* TXDIS  (TX_DIS)       */
#define XUARTPS_CR_TXEN    (1<<4)       /* TXEN   (TX_EN)        */
#define XUARTPS_CR_RXDIS   (1<<3)       /* RXDIS  (RX_DIS)       */
#define XUARTPS_CR_RXEN    (1<<2)       /* RXEN   (RX_EN)        */
#define XUARTPS_CR_TXRES   (1<<1)       /* TXRES  (TXRST)        */
#define XUARTPS_CR_RXRES   (1<<0)       /* RXRES  (RXRST)        */

/*
 * MODER (0x00000004)
 */
#define XUARTPS_MR_PAR                  /* PAR (Parity)          */
#define XUARTPS_MR_PAR_EVEN     0       /* 000 : Even            */
                                        /* 001 : Odd             */
                                        /* 010 : Space           */
                                        /* 011 : Mark            */
#define XUARTPS_MR_PAR_NONE (1<<5)      /* 1xx : No parity       */

#define XUARTPS_MR_CHRL                 /* CHRL (Char Length)    */
                                        /*  11 : 6 bits          */
                                        /*  10 : 7 bits          */
#define XUARTPS_MR_CHRL_8               /*  0x : 8 bits          */

#define XUARTPS_MR_CLKS                 /* CLKS (Clock Source)   */
#define XUARTPS_MR_CLKS_REF_CLK 0       /*   0 : uart_ref_clk    */
                                        /*   1 : uart_ref_clk/8  */

/*
 * CSR (0x0000002C)
 */
#define UART_STS_TXFULL  (1<<4)         /* TX FIFO Buffer Status */
                                        /*  1 : FIFO full        */
                                        /*  0 : FIFO not full    */
#define UART_STS_TXEMPTY (1<<3)         /* TX FIFO Buffer Status */
                                        /*  1 : FIFO not empty   */
                                        /*  0 : FIFO empty       */
#define UART_STS_RXFULL  (1<<2)         /* RX FIFO Buffer Status */
                                        /*  1 : FIFO full        */
                                        /*  0 : FIFO not full    */
#define UART_STS_RXEMPTY (1<<1)         /* RX FIFO Buffer Status */
                                        /*  1 : FIFO not empty   */
                                        /*  0 : FIFO empty       */


struct XUARTPS
{
    uint32_t CR;            /* UART Control Register */
    uint32_t MODER;         /* UART Mode Register */
    uint32_t IER;           /* Interrupt Enable Register */
    uint32_t IDR;           /* Interrupt Disable Register */
    uint32_t IMR;           /* Interrupt Mask Register */
    uint32_t CISR;          /* Channel Interrupt Status Register */
    uint32_t BRGR;          /* Baud Rate Generator Register */
    uint32_t RTR;           /* Receiver Timeout Register */
    uint32_t RX_FIFO_TLR;   /* Receiver FIFO Trigger Level Register */
    uint32_t MCR;           /* Modem Control Register */
    uint32_t MSR;           /* Modem Status Register */
    uint32_t CSR;           /* Channel Status Register */
    uint32_t TX_RX_FIFO0;   /* Transmit and Receive FIFO */
    uint32_t BRDR;          /* Baud Rate Divider */
    uint32_t FDR;           /* Flow Control Delay Register */
    uint32_t TX_FIFO_TLR;   /* Transmitter FIFO Trigger Level Register */
};

static unsigned int default_uart_id;
static struct XUARTPS *UART1 = (struct XUARTPS*) UART1_BASE;
static struct XUARTPS *UART2 = (struct XUARTPS*) UART2_BASE;

static struct XUARTPS *uart_interfaces[UART_ID_NUM] =
{
    [UART1_ID] = (struct XUARTPS*) UART1_BASE,
    [UART2_ID] = (struct XUARTPS*) UART2_BASE,
};

void uart_init(uart_id_t uart_id)
{
    struct XUARTPS *uart = uart_interfaces[uart_id];

    /* Disable UART */
    uart->CR = 0;

    /* 115200 8N1 */
    uart->BRDR = XUARTPS_BDIV_CD_115200;
    uart->BRGR = XUARTPS_BRGR_CD_115200;
    uart->MODER = XUARTPS_MR_PAR_NONE;
    
    /* Enable UART */
    uart->CR =  (XUARTPS_CR_TXEN | XUARTPS_CR_RXEN | XUARTPS_CR_TXRES | XUARTPS_CR_RXRES);
}

uint8_t uart_read_byte(uart_id_t uart_id)
{
    struct XUARTPS *uart = uart_interfaces[uart_id];

    while( ( (uart->CSR) & UART_STS_RXEMPTY) > 0);

    return (uint8_t)(uart->TX_RX_FIFO0);
}

void uart_write_byte(uart_id_t uart_id, uint8_t ch)
{
    struct XUARTPS *uart = uart_interfaces[uart_id];

    while( ( (uart->CSR) & UART_STS_TXFULL) > 0);

    uart->TX_RX_FIFO0 = (uint32_t)(ch); /* Transmit char */
}

void uart_write_bytes(uart_id_t uart_id, uint8_t *string)
{
    while (*string != '\0')
    {
        uart_write_byte(uart_id, (uint8_t) *string);
        string++;
    }
}