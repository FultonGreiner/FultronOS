#ifndef __STDOUT_H__
#define __STDOUT_H__

#include <stdint.h>

// default stdout to uart
#ifndef STDOUT_BASE
    #define STDOUT_BASE UART_BASE
#endif

typedef volatile uint32_t stdout_t;

extern stdout_t *stdout;

#endif /* __STDOUT_H__ */
