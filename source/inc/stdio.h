#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdint.h>
#include <stdarg.h>

#include "uart.h"

void kputc(char, uart_t*);
// void kprintf(const char *, uart_t*, ...);
void kprintf(const char *s, uart_t *addr, ...);

#endif                                                          /* _STDIO_H_ */