#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <stdint.h>

#include "../../../../kernel/include/uart.h"
#include "stdout.h"

extern stdout_t *stdout;

void putc(char, uart_t*);
// int putc(int c, void *addr);
// void printf(const char *, ...);
// int printf(const char *s, ...);

#endif /* __STDIO_H__ */
