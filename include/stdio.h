#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdint.h>
#include <stdarg.h>

#include "../include/uart.h"

void putc(char, uart_t*);
void printf(const char *, uart_t*, ...);

#endif                                                          /* _STDIO_H_ */