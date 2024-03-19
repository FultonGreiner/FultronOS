#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stdio.h"

void kernel_main(void) 
{
	float f = 2.66666;
	kprintf("\nHello, world %f!\n", f);
}
