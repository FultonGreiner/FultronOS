#include <stdint.h>

#include "sdram.h"

#define DDR0_BASE (0x00100000ULL)
#define DDR0_SIZE (0x20000000ULL) /* 512M (512 * 1024 * 1024) */

void flash_read(uint32_t address, uint8_t *data, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        data[i] = *((uint8_t *)(address + i));
    }
    return;
}

void flash_write(uint32_t address, const uint8_t *data, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        *((volatile uint8_t *)(address + i)) = data[i];
    }
    return;
}