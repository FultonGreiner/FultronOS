#ifndef __MEMORY_MAP_H__
#define __MEMORY_MAP_H__

#include <stdint.h>

extern void PUT32(uint32_t address, uint32_t value);
extern uint32_t GET32(uint32_t address);

#endif /* __MEMORY_MAP_H__ */
