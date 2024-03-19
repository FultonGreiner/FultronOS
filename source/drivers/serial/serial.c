/**
 * @file
 *
 * @brief Serial driver source file
 */

/*
 *
 * Copyright (c) 2024 Charles Fulton Greiner <fultongreiner@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Author: Charles Fulton Greiner <fultongreiner@gmail.com>
 */


#include "serial.h"

#include <stdint.h>

#define SERIAL_COM1 0x3f8
#define SERIAL_COM2 0x2f8
#define SERIAL_PORT SERIAL_COM1

#define SERIAL_THR 0
#define SERIAL_LSR 5

static void io_write_8(const uint16_t port, const uint8_t val);
static uint8_t io_read_8(const uint16_t port);

/**
 * @brief Write to I/O port
 */
static void io_write_8(const uint16_t port, const uint8_t val)
{
	asm volatile(
		"outb    %%al, %%dx;"
		/* Outputs  */ : /* None */
		/* Inputs   */ : "a" (val), "d" (port)
		/* Clobbers */ : /* None */
		);
}

/**
 * @brief Write to I/O port
 */
static uint8_t io_read_8(const uint16_t port)
{
	uint8_t val;

	asm volatile(
		"inb     %%dx, %%al;"
		/* Outputs  */ : "=a" (val)
		/* Inputs   */ : "d" (port)
		/* Clobbers */ : /* None */
		);

	return val;
}

/**
 * @brief Print a character to the serial port
 */
int _putchar(const char c)
{
	/* Wait for THRE (bit 5) to be high */
	while ( ( io_read_8(SERIAL_PORT + SERIAL_LSR) & (1<<5) ) == 0)
    {
        /* Do nothing */
    }

	io_write_8(SERIAL_PORT + SERIAL_THR, c);

	return c;
}