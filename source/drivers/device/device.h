#ifndef _DEVICE_H
#define _DEVICE_H

#include <stdint.h>

typedef struct device
{
    void (*init)(void);
    void (*read_byte)(void);
    void (*write_byte)(uint8_t);
    void (*write_string)(char *);
} device_t;

#endif /* _DEVICE_H */