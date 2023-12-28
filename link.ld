/* specify entry point */
/* ENTRY(_start) */

MEMORY
{
    ram : ORIGIN = 0x0, LENGTH = 0x1B400
}

SECTIONS
{
    .text : { *(.text*) } > ram
    .bss : { *(.bss*) } > ram
}

/* */
/* SECTIONS
{ */
    /* set current memory address */
    /* . = 0x80010000; */

    /* `.stub` <- `.text` section from `_start.o` */
    /* .stub   : { _start.o(.text) } */
    /* `.text` <- main */
    /* .text   : { *(.text) } */
    /* `.rodata` <- read-only data */
    /* .rodata : { *(.rodata) } */
    /* `.data` <- initialized data */
    /* .data   : { *(.data) } */
    /* `.bss` <- uninitialized data */
    /* .bss    : { *(.bss COMMON) } */
 
    /* set current address to `stack_base` */
    /* stack_base = .; */
    /* increment current address (reserves 65536 bytes of memory) */
    /* . += 0x10000; */
    /* set current address to `stack_top` */
    /* stack_top = .; */
/* } */
