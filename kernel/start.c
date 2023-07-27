#include <stdint.h>
// #include <math.h>

#include "../include/stdio.h"
#include "../include/uart.h"

uart_t *uart = (uint8_t *) UART_BASE;

void start() {
    int d = (int) (3.0f / 1.0f);
    // float f = 3.0f;
    printf("3^3 = %d\n", uart, d);
    // printf("3^3 = %d\n", uart, (int) pow(3, 3));
    // printf("10/5 = %s\n", uart, "This is a string");
    // printf("10/5 = %c\n", uart, 'c');
    // printf("10/5 = %f\n", uart, 12345.0f);
}
