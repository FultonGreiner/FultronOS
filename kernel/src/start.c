#include <stdint.h>

#include "../include/gpio.h"
#include "../include/memory_map.h"

#define TIME 				(500000ULL)

void start(void)
{
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
