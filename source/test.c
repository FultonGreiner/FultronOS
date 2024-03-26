#include <stdint.h>

#include "xparameters.h"
#include "xuartps.h"

#define UART0_DEVICE_ID (XPAR_XUARTPS_0_DEVICE_ID)

// #define XUARTPS_CR_STOPBRK (1<<8)       /* STPBRK (STOPBRK)      */
// #define XUARTPS_CR_STTBRK  (1<<7)       /* STTBRK (STARTBRK)     */
// #define XUARTPS_CR_RSTTO   (1<<6)       /* RSTTO  (TORST)        */
// #define XUARTPS_CR_TXDIS   (1<<5)       /* TXDIS  (TX_DIS)       */
#define XUARTPS_CR_TXEN    (1<<4)       /* TXEN   (TX_EN)        */
// #define XUARTPS_CR_RXDIS   (1<<3)       /* RXDIS  (RX_DIS)       */
#define XUARTPS_CR_RXEN    (1<<2)       /* RXEN   (RX_EN)        */
#define XUARTPS_CR_TXRES   (1<<1)       /* TXRES  (TXRST)        */
#define XUARTPS_CR_RXRES   (1<<0)       /* RXRES  (RXRST)        */

int UartPsHelloWorldExample(uint16_t DeviceId);

XUartPs uart0;

int main(void)
{
	int Status;

	Status = UartPsHelloWorldExample(UART0_DEVICE_ID);
	if ( XST_FAILURE == Status )
	{
		return XST_FAILURE;
	}

	return Status;
}

int UartPsHelloWorldExample(uint16_t DeviceId)
{
	uint8_t rx_buffer[] = "Hello World";
	int SentCount = 0;
	int Status;
	// XUartPs_Config *Config;

	XUartPs_Config uart0_config = {
		.DeviceId = XPAR_XUARTPS_0_DEVICE_ID,
		.BaseAddress = XPAR_XUARTPS_0_BASEADDR,
		.InputClockHz = XPAR_XUARTPS_0_UART_CLK_FREQ_HZ,
	};

	// XUartPsFormat uart0_format = {
	// 	.BaudRate = 115200,
	// 	.DataBits = XUARTPS_FORMAT_8_BITS,
	// 	.Parity = XUARTPS_FORMAT_NO_PARITY,
	// 	.StopBits = XUARTPS_FORMAT_1_STOP_BIT,
	// };

	// Config = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);

	// Status = XUartPs_CfgInitialize(&uart0, Config, Config->BaseAddress);
	Status = XUartPs_CfgInitialize(&uart0, &uart0_config, uart0_config.BaseAddress);
	if ( XST_SUCCESS != Status )
	{
		return XST_FAILURE;
	}

	XUartPs_SetBaudRate(&uart0, 115200);

	// XUartPs_WriteReg(uart0_config.BaseAddress, RegOffset, RegisterValue);
	// XUartPs_SetModeControl(&uart0, XUARTPS_CR_TXEN | XUARTPS_CR_RXEN | XUARTPS_CR_TXRES | XUARTPS_CR_RXRES);
	// XUartPs_SetDataFormat(&uart0, &uart0_format);

	while (SentCount < (sizeof(rx_buffer) - 1))
	{
		/* Transmit the data */
		SentCount += XUartPs_Send(&uart0, &rx_buffer[SentCount], 1);
	}

	return SentCount;
}