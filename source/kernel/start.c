// #include <stdio.h>
#include <stdint.h>
#include <string.h>
// #include <math.h>

// #include "stdio.h"
// #include "uart.h"
#include "printf.h"

// uart_t *uart = (uint8_t *) UART_BASE;

void start()
{
    int d = (int) (3.0f / 1.0f);
    printf("3.0 / 1.0 = %d\n", d);

    // double f = 3.0f / 4.0f;
    float f = 0.666;
    printf("0.666 = %f\n", f);

    // double f2 = (float)d;
    float f2 = 3.0f / 4.0f;
    printf("3 / 4 = %f\n", f2);

    printf("3 / 4 = %x\n", f2);
    // kprintf("3.0 / 1.0 = %d\n", uart, d);
}
