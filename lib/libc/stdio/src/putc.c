#include "../inc/stdio.h"

// int putc(int c, void *addr) {
//     *(char*)addr = c;
//     return 0;
// }

void putc(char c, stdout_t *addr) {
    *addr = c;
}
