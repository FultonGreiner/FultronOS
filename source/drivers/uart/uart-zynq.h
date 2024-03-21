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
 * Control_reg0 (0x00000000)
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
 * mode_reg0 (0x00000004)
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
 * Channel_sts_reg0 (0x0000002C)
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
    uint32_t Control_reg0;             /* UART Control Register                   */
    uint32_t mode_reg0;                /* UART Mode Register                      */
    uint32_t Intrpt_en_reg0;           /* Interrupt Enable Register               */
    uint32_t Intrpt_dis_reg0;          /* Interrupt Disable Register              */
    uint32_t Intrpt_mask_reg0;         /* Interrupt Mask Register                 */
    uint32_t Chnl_int_sts_reg0;        /* Channel Interrupt Status Register       */
    uint32_t Baud_rate_gen_reg0;       /* Baud Rate Generator Register            */
    uint32_t Rcvr_timeout_reg0;        /* Receiver Timeout Register               */
    uint32_t Rcvr_FIFO_trigger_level0; /* Receiver FIFO Trigger Level Register    */
    uint32_t Modem_ctrl_reg0;          /* Modem Control Register                  */
    uint32_t Modem_sts_reg0;           /* Modem Status Register                   */
    uint32_t Channel_sts_reg0;         /* Channel Status Register                 */
    uint32_t TX_RX_FIFO0;              /* Transmit and Receive FIFO               */
    uint32_t Baud_rate_divider_reg0;   /* Baud Rate Divider                       */
    uint32_t Flow_delay_reg0;          /* Flow Control Delay Register             */
    uint32_t Tx_FIFO_trigger_level0;   /* Transmitter FIFO Trigger Level Register */
};

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

#endif /* _UART_ZYNQ_H */