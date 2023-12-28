#include <stdint.h>

// #include <math.h>

#include "../lib/libc/stdio/inc/stdio.h"

stdout_t *stdout = (stdout_t*) STDOUT_BASE;

void start(void)
{
    int d = 10;
    printf("float = %d\n", d);

    // printf("string = %s\n", "string");
}
