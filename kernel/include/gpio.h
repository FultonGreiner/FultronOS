#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdbool.h>
#include <stdint.h>

bool gpio_init(uint32_t mode);
void gpio_set(uint32_t mode);
void gpio_clear(uint32_t mode);

#endif /* __GPIO_H__ */
