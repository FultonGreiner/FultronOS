#include <stdint.h>

#include "../include/stdio.h"

stdout_t *stdout = (stdout_t*) STDOUT_BASE;

void start(void)
{
    printf("Hello, world!\n");
}
