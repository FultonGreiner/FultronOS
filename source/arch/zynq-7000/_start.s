.syntax unified     /* Use the unified instruction syntax */
.arm                /* Assemble ARM instruction set, not thumb */

.global g_pfnVectors

    .section .text.Reset_Handler
    .weak Reset_Handler
    .type Reset_Handler, %function

Reset_Handler:
    ldr sp, =__stack_top
    bl main
    b .

    .section .isr_vector,"a",%progbits
    .type g_pfnVectors, %object
    .size g_pfnVectors, .-g_pfnVectors

/**
 * @brief Vector Table
 *
 * Exception                Processor Mode          Event                    Return Sequence
 */
g_pfnVectors:
    .word Reset_Handler             /* MODE_SVC          System Reset                n/a                          */
    .word undef_handler             /* MODE_UNDEFINED    Undefined Instruction       MOVS PC, LR (if emulating)   */
    .word SVC_handler               /* MODE_SVC          SVC instruction             MOVS PC, LR                  */
    .word prefetch_abort_handler    /* MODE_ABORT        Invalid inst. address       SUBS PC, LR, #4              */
    .word data_abort_handler        /* MODE_ABORT        R/W to invalid address      SUBS PC, LR, #8 (to retry)   */
    .word hypervisor_handler        /* MODE_HYP          Hypervisor entry            ERET                         */
    .word IRQ_handler               /* MODE_IRQ          IRQ Input Asserted          SUBS PC, LR, #4              */
    .word FIQ_handler               /* MODE_FIQ          FIQ Input Asserted          SUBS PC, LR, #4              */

@ undef_handler:
@     b undef_handler

@ SVC_handler:
@     b SVC_handler

@ prefetch_abort_handler:
@     b prefetch_abort_handler

@ data_abort_handler:
@     b data_abort_handler

@ hypervisor_handler:
@     b hypervisor_handler

@ IRQ_handler:
@ 	/* IRQ only used for scheduling */
@     b IRQ_handler

@ FIQ_handler:
@     b FIQ_handler
