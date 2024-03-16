#include <stdint.h>
// #include <stdio.h>
// #include <math.h>

#include "stdio.h"
#include "uart.h"

uart_t *uart = (uint8_t *) UART_BASE;

void start()
{
    int d = (int) (3.0f / 1.0f);
    float f = 3.0f;
    // kprintf("3^3 = %d\n", d);
    kprintf("3.0 / 1.0 = %d\n", uart, d);
    kprintf("3.0 = %f\n", uart, f);
}
