#include <stdint.h>

#include "../include/stdio.h"
#include "../include/uart.h"

uart_t *uart = (uint8_t *) UART_BASE;

void start() {
    printf("10/5 = %d\n", uart, 10 / 5);
}
