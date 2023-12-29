OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

/* specify entry point */
ENTRY(_start)

MEMORY
{
   ram : ORIGIN = 0x402f0400, LENGTH = 0x1B400
   public_stack : ORIGIN = 0x4030B800, LENGTH = 0x1600
}

C_STACK_SIZE   = 4K;
IRQ_STACK_SIZE = 128;
FIQ_STACK_SIZE = 128;
SVC_STACK_SIZE = 128;
ABT_STACK_SIZE = 128;
UND_STACK_SIZE = 128;

SECTIONS
{
    .text : { *(.text*) } > ram
    .rodata : { *(.rodata*) } > ram
    .data : { *(.data*) } > ram

    .bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
    } > ram

    .stack :
    {
        __stack_start__ = .;

        . += IRQ_STACK_SIZE;
        . = ALIGN(4);
        __irq_stack_top__ = .;

        . += FIQ_STACK_SIZE;
        . = ALIGN(4);
        __fiq_stack_top__ = .;

        . += SVC_STACK_SIZE;
        . = ALIGN(4);
        __svc_stack_top__ = .;

        . += ABT_STACK_SIZE;
        . = ALIGN(4);
        __abt_stack_top__ = .;

        . += UND_STACK_SIZE;
        . = ALIGN(4);
        __und_stack_top__ = .;

        . += C_STACK_SIZE;
        . = ALIGN(4);
        __c_stack_top__ = .;

        __stack_end__ = .;
    } > public_stack
}

/* set interrupt vector table address */
. = 0x4030CE00;
__isr_table_start__ = .;
