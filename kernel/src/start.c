#include <stdint.h>

#include "../include/gpio.h"
#include "../include/memory_map.h"
// #include "gpio.h"
// #include "memory_map.h"
#include "stdio.h"
#include "stdout.h"

#define TIME 				(500000ULL)
stdout_t *stdout = (stdout_t*) STDOUT_BASE;

void start(void)
{
	// printf("Hello, world!\n");
	// putc((int)'A', stdout);
	*stdout = 1;

	gpio_init((1 << 18) | 2);

	volatile uint32_t ra;
	while (1)
	{
		gpio_set(15 << 21);
		for (ra = 0; ra < TIME; ra++);
		gpio_clear(15 << 21);
		for (ra = 0; ra < TIME; ra++);
	}
   return;
}
