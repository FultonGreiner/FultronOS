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

/**
 * @brief Vector Table
 *
 * Exception                Processor Mode          Event                    Return Sequence
 */
    .section .isr_vector

    b Reset_Handler             /* MODE_SVC          System Reset                n/a                          */
    b undef_handler             /* MODE_UNDEFINED    Undefined Instruction       MOVS PC, LR (if emulating)   */
    b SVC_handler               /* MODE_SVC          SVC instruction             MOVS PC, LR                  */
    b prefetch_abort_handler    /* MODE_ABORT        Invalid inst. address       SUBS PC, LR, #4              */
    b data_abort_handler        /* MODE_ABORT        R/W to invalid address      SUBS PC, LR, #8 (to retry)   */
    b hypervisor_handler        /* MODE_HYP          Hypervisor entry            ERET                         */
    b IRQ_handler               /* MODE_IRQ          IRQ Input Asserted          SUBS PC, LR, #4              */
    b FIQ_handler               /* MODE_FIQ          FIQ Input Asserted          SUBS PC, LR, #4              */

    .text

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
