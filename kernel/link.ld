/* specify entry point */
ENTRY(_start)

/* */
SECTIONS
{
    /* set current memory address */
    . = 0x80010000;

    /* `.stub` <- `.text` section from `_start.o` */
    .stub   : { _start.o(.text) }
    /* `.text` <- main */
    .text   : { *(.text) }
    /* `.rodata` <- read-only data */
    .rodata : { *(.rodata) }
    /* `.data` <- initialized data */
    .data   : { *(.data) }
    /* `.bss` <- uninitialized data */
    .bss    : { *(.bss COMMON) }
 
    /* set current address to `STACK_BASE` */
    STACK_BASE = .;
    /* increment current address (reserves 65536 bytes of memory) */
    . += 0x10000;
    /* set current address to `STACK_TOP` */
    STACK_TOP = .;
}
