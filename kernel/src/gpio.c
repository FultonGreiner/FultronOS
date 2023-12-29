#include "../include/gpio.h"

#include <stdbool.h>
#include <stdint.h>

#include "../include/memory_map.h"

#define GPIO1_BASE			(0x4804C000ULL)
#define GPIO_SYSCONFIG		(0x10ULL)
#define GPIO_SYSSTATUS		(0x114ULL)
#define GPIO_OE				(0x134ULL)
#define GPIO_CLRDATAOUT		(0x190ULL)
#define GPIO_SETDATAOUT		(0x194ULL)

#define CM_PER_BASE			(0x44e00000ULL)
#define CM_PER_GPIO1		(0xACULL)

// TODO - use enum for GPIO1, GPIO2, etc.

bool gpio_init(uint32_t mode)
{
    volatile uint32_t ra;
    bool success = false;

	PUT32(CM_PER_BASE + CM_PER_GPIO1, mode);
	ra = GET32(GPIO1_BASE + GPIO_OE);
	ra &= ~(15 << 21);
	PUT32(GPIO1_BASE + GPIO_OE, ra);

    success = (ra == GET32(GPIO1_BASE + GPIO_OE) );

    return success;
}

void gpio_set(uint32_t value)
{
    PUT32(GPIO1_BASE + GPIO_SETDATAOUT, value);
}

void gpio_clear(uint32_t value)
{
    PUT32(GPIO1_BASE + GPIO_CLRDATAOUT, value);
}
