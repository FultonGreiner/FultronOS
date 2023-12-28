#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <stdint.h>

#include "../../../../include/uart.h"
#include "stdout.h"

extern stdout_t *stdout;

void putc(char, uart_t*);
void printf(const char *, ...);

#endif /* __STDIO_H__ */
