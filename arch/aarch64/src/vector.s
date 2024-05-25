/**
 * @file vector.s
 * @brief Exception vector table and handlers for AArch64.
 *
 * This file defines the exception vector table and exception handlers for
 * various exception levels and types for the AArch64 architecture.
 * @date 2024-05-24
 * @version 1.0
 * @author Charles Fulton Greiner
 *
 * @details
 * The exception vector table is aligned as required by the ARMv8-A architecture
 * and includes handlers for synchronous exceptions, IRQs, FIQs, and SErrors.
 * The handlers save the exception context, call a handler function, and restore
 * the context.
 *
 * @section license License
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @section description Description
 * Exception vector table and handlers for AArch64.
 *
 * @section examples Examples
 * No examples available for exception handling code.
 */

/**
 * @brief Save frame context, call IRQ handler function, and recover.
 *
 * This macro saves the current frame context on the stack, calls the
 * specified handler function with the context as the first argument, and
 * restores the context after the handler returns.
 *
 * @param handler The handler function to call.
 */

.macro IRQ_RECOVER handler
__irq_\handler:
    bl save_interrupt_frame

    // Call the handler function.
    bl \handler

    // Restore the exception context and return from the exception.
    b restore_interrupt_frame

.size __irq_\handler, . - __irq_\handler
.type __irq_\handler, function
.endm

//--------------------------------------------------------------------------------------------------
// Private Code
//--------------------------------------------------------------------------------------------------
.section .text

//------------------------------------------------------------------------------
// The exception vector table.
//------------------------------------------------------------------------------

/**
 * @brief Exception vector table for AArch64.
 *
 * This table defines the exception vectors for various exception levels and types,
 * and uses macros to handle the exceptions by saving the context and calling the
 * appropriate handler functions.
 */

// Align by 2^11 bytes, per ARMv8-A spec.
.align 11

.global vectors
vectors:
	.balign 0x80
		IRQ_RECOVER elnt_sync_invalid
	.balign 0x80
		IRQ_RECOVER elnt_irq_invalid
	.balign 0x80
		bl __suspend_until_irq
	.balign 0x80
		IRQ_RECOVER elnt_error_invalid

	// Current exception level with SP_ELx, x > 0.
	.balign 0x80
		IRQ_RECOVER elnh_sync_invalid
	.balign 0x80
		IRQ_RECOVER elnh_irq_invalid
	.balign 0x80
		bl __suspend_until_irq
	.balign 0x80
		IRQ_RECOVER elnh_error_invalid

	// Lower exception level, AArch64
	.balign 0x80
		IRQ_RECOVER eln_sync_aarch64
	.balign 0x80
		IRQ_RECOVER eln_irq_aarch64
	.balign 0x80
		bl __suspend_until_irq
	.balign 0x80
		IRQ_RECOVER eln_error_invalid_aarch64

	// Lower exception level, AArch32
	.balign 0x80
		IRQ_RECOVER eln_sync_aarch32
	.balign 0x80
		IRQ_RECOVER eln_irq_aarch32
	.balign 0x80
		bl __suspend_until_irq
	.balign 0x80
		IRQ_RECOVER eln_error_invalid_aarch32
	.balign 0x80

/**
 * @brief Restore the interrupt frame context.
 *
 * This function restores the saved interrupt frame context from the stack and 
 * returns from the exception using the 'eret' instruction.
 */
restore_interrupt_frame:
    ldr w19, [sp, #16 * 16]
    ldp lr, x20, [sp, #16 * 15]

    msr SPSR_EL1, x19
    msr ELR_EL1, x20

    ldp x0, x1, [sp, #16 * 0]
    ldp x2, x3, [sp, #16 * 1]
    ldp x4, x5, [sp, #16 * 2]
    ldp x6, x7, [sp, #16 * 3]
    ldp x8, x9, [sp, #16 * 4]
    ldp x10, x11, [sp, #16 * 5]
    ldp x12, x13, [sp, #16 * 6]
    ldp x14, x15, [sp, #16 * 7]
    ldp x16, x17, [sp, #16 * 8]
    ldp x18, x19, [sp, #16 * 9]
    ldp x20, x21, [sp, #16 * 10]
    ldp x22, x23, [sp, #16 * 11]
    ldp x24, x25, [sp, #16 * 12]
    ldp x26, x27, [sp, #16 * 13]
    ldp x28, x29, [sp, #16 * 14]

    add sp, sp, #16 * 17

    eret

.size restore_interrupt_frame, . - restore_interrupt_frame
.type restore_interrupt_frame, function

/**
 * @brief Save the interrupt frame context.
 *
 * This function stores the saved interrupt frame context to the stack and 
 * returns to continue executing the exception using the 'ret' instruction.
 */
save_interrupt_frame:
    // Allocate space on the stack for the exception context (17 registers).
    sub sp, sp, #16 * 17

    // Save all general-purpose registers on the stack.
    stp x0, x1, [sp, #16 * 0]
    stp x2, x3, [sp, #16 * 1]
    stp x4, x5, [sp, #16 * 2]
    stp x6, x7, [sp, #16 * 3]
    stp x8, x9, [sp, #16 * 4]
    stp x10, x11, [sp, #16 * 5]
    stp x12, x13, [sp, #16 * 6]
    stp x14, x15, [sp, #16 * 7]
    stp x16, x17, [sp, #16 * 8]
    stp x18, x19, [sp, #16 * 9]
    stp x20, x21, [sp, #16 * 10]
    stp x22, x23, [sp, #16 * 11]
    stp x24, x25, [sp, #16 * 12]
    stp x26, x27, [sp, #16 * 13]
    stp x28, x29, [sp, #16 * 14]

    mrs	x1,  elr_el2
	mrs	x2,  spsr_el2
	mrs	x3,  esr_el2

    ret

/**
 * @brief Suspend execution until an another IRQ is received.
 *
 * This function suspends the execution of the current thread until an interrupt
 * is received by executing the 'wfe' (wait for event) instruction in a loop, 
 * before eventually returning.
 */
__suspend_until_irq:
    1:  wfe
        b 1b
    ret

.size __suspend_until_irq, . - __suspend_until_irq
.type __suspend_until_irq, function

.size save_interrupt_frame, . - save_interrupt_frame
.type save_interrupt_frame, function
