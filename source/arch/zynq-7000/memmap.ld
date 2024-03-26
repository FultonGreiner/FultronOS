/* ENTRY(_start) */

_HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x10000;    /* 64kB of heap memory */
_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0x10000; /* 64kB of stack memory */

/* _OCM_RAM0_BASEADDR = 0x00000000;
_OCM_RAM0_LENGTH = 192K;

_OCM_ROM_BASEADDR = _OCM_RAM0_BASEADDR + _OCM_RAM0_LENGTH;
_OCM_ROM_LENGTH = 64K;

_EMPTY0_BASEADDR = _OCM_ROM_BASEADDR + _OCM_ROM_LENGTH;
_EMPTY0_LENGTH = 768K;

_DDR_BASEADDR = _EMPTY0_BASEADDR + _EMPTY0_LENGTH;
_DDR_LENGTH = 2G; */

/* Define Memories in the system */
MEMORY
{
	PMU_RAM : ORIGIN = 0xFFDC0000, LENGTH = 0x1F6E0	    ~125.7 k
    /* OCM_RAM0 : ORIGIN = _OCM_RAM0_BASEADDR, LENGTH = _OCM_RAM0_LENGTH
    OCM_ROM  : ORIGIN = _OCM_ROM_BASEADDR,  LENGTH = _OCM_ROM_LENGTH
    EMPTY0   : ORIGIN = _EMPTY0_BASEADDR,   LENGTH = _EMPTY0_LENGTH
    DDR      : ORIGIN = 0x00000000,         LENGTH = 0x80000000
    M_AXI_GP0
    M_AXI_GP1
    PERIPHERALS
    EMPTY1
    OCM_RAM1 */
}

SECTIONS
{
    .text 0xFFDC0050: {
        *(.text)
        *(.text.*)
        *(.gnu.linkonce.t.*)
    } > PMU_RAM

    .rodata : {
        __rodata_start = .;
        *(.rodata)
        *(.rodata.*)
        *(.gnu.linkonce.r.*)
        __rodata_end = .;
    } > PMU_RAM

    .data : {
        . = ALIGN(4);
        __data_start = .;
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d.*)
        __data_end = .;
    } > PMU_RAM

    .bss (NOLOAD) : {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > PMU_RAM

    .heap (NOLOAD) : {
        . = ALIGN(8);
        __heap_start = .;
        . = . + _HEAP_SIZE;
        . = ALIGN(8);
        __heap_end = .;
    } > PMU_RAM

    /* Generate Stack definitions */
    .stack (NOLOAD) : {
        . = ALIGN(8);
        __stack_end = .;
        . += _STACK_SIZE;
        . = ALIGN(8);
        __stack_top = .;
    } > PMU_RAM

    _end = .;
}
