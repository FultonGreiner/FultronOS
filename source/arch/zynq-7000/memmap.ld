OUTPUT_FORMAT("elf32-littlearm")

_HEAP_SIZE  = DEFINED(_HEAP_SIZE)  ? _HEAP_SIZE  : 16K; /* 16K of heap memory */
_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 16K; /* 16K of stack memory */

/* Define memory regions */
MEMORY
{
    SRAM0      : ORIGIN = 0x00000000, LENGTH = 192K /* 192K */
    DDR0       : ORIGIN = 0x00100000, LENGTH = 512M /* 512M */
    QSPI_FLASH : ORIGIN = 0xFC000000, LENGTH = 16M  /* 16M */
    SRAM1      : ORIGIN = 0xFFFF0000, LENGTH = 64K  /* 64K */
}

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector)) /* Startup code */
    } > SRAM0

    .text :
    {
        *(.text)
        *(.text.*)
        *(.gnu.linkonce.t.*)
    } > SRAM0

    .rodata :
    {
        __rodata_start = .;
        *(.rodata)
        *(.rodata.*)
        *(.gnu.linkonce.r.*)
        __rodata_end = .;
    } > SRAM0

    .data :
    {
        . = ALIGN(4);
        __data_start = .;
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d.*)
        __data_end = .;
    } > SRAM0

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > SRAM0

    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        __heap_start = .;
        . = . + _HEAP_SIZE;
        . = ALIGN(8);
        __heap_end = .;
    } > SRAM1

    /* Generate Stack definitions */
    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        __stack_end = .;
        . += _STACK_SIZE;
        . = ALIGN(8);
        __stack_top = .;
    } > SRAM1

    _end = .;
}
