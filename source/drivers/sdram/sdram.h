#ifndef _SDRAM_H
#define _SDRAM_H

#include <stdint.h>

void flash_write(uint32_t address, const uint8_t *data, uint32_t size);
void flash_read(uint32_t address, uint8_t *data, uint32_t size);

#endif /* _SDRAM_H */