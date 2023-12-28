#include "../inc/stdio.h"

void putc(char c, stdout_t *addr) {
    *addr = c;
}
