#include <stdint.h>
// #include <stdio.h>
// #include <math.h>

#include "stdio.h"
#include "uart.h"

uart_t *uart = (uint8_t *) UART_BASE;

void start() {
    int d = (int) (3.0f / 1.0f);
    // float f = 3.0f;
    // kprintf("3^3 = %d\n", d);
    kprintf("3.0 / 1.0 = %d\n", uart, d);
    // printf("10/5 = %s\n", uart, "This is a string");
    // printf("10/5 = %c\n", uart, 'c');
    // printf("10/5 = %f\n", uart, 12345.0f);
}
