//! Exception vector handling for AArch64.
//!
//! This module provides definitions and handlers for various exceptions in the AArch64
//! architecture. It includes the interrupt frame structure, default handlers, and
//! initialization functions for the exception vectors.

use aarch64_cpu::asm::*;
use aarch64_cpu::registers::*;
use core::cell::UnsafeCell;
use core::fmt;
use tock_registers::interfaces::{Readable, Writeable};

/// Structure representing the saved state of general-purpose registers and other CPU state
/// during an interrupt or exception.
#[repr(C)]
pub struct InterruptFrame {
    /// General-purpose registers x0 - x29.
    gp: [u64; 30],
    /// Exception Link Register.
    elr: u64,
    /// Saved Program Status Register.
    spsr: u64,
    /// Exception Syndrome Register.
    esr: u64,
}

/// Default IRQ handler which panics and displays the interrupt frame.
fn default_irq_handler(frame: &InterruptFrame) {
    panic!(
        "IRQ!\n\n\
        {}",
        frame
    );
}

/// Synchronous exception handler for an invalid exception level.
#[no_mangle]
extern "C" fn elnt_sync_invalid(_frame: &mut InterruptFrame) {
    panic!("Entered elnt_sync_invalid()!")
}

/// IRQ handler for an invalid exception level.
#[no_mangle]
extern "C" fn elnt_irq_invalid(_frame: &mut InterruptFrame) {
    panic!("Entered elnt_irq_invalid()!")
}

/// Error handler for an invalid exception level.
#[no_mangle]
extern "C" fn elnt_error_invalid(_frame: &mut InterruptFrame) {
    panic!("Entered elnt_error_invalid()!")
}

/// Synchronous exception handler for an invalid hypervisor level.
#[no_mangle]
extern "C" fn elnh_sync_invalid(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// IRQ handler for an invalid hypervisor level.
#[no_mangle]
extern "C" fn elnh_irq_invalid(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// Error handler for an invalid hypervisor level.
#[no_mangle]
extern "C" fn elnh_error_invalid(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// Synchronous exception handler for a lower exception level (AArch64).
#[no_mangle]
extern "C" fn eln_sync_aarch64(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// IRQ handler for a lower exception level (AArch64).
#[no_mangle]
extern "C" fn eln_irq_aarch64(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// Error handler for an invalid exception level (AArch64).
#[no_mangle]
extern "C" fn eln_error_invalid_aarch64(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// Synchronous exception handler for a lower exception level (AArch32).
#[no_mangle]
extern "C" fn eln_sync_aarch32(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// IRQ handler for a lower exception level (AArch32).
#[no_mangle]
extern "C" fn eln_irq_aarch32(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// Error handler for an invalid exception level (AArch32).
#[no_mangle]
extern "C" fn eln_error_invalid_aarch32(frame: &mut InterruptFrame) {
    default_irq_handler(frame);
}

/// Implements the `Display` trait for `InterruptFrame` to print the register states.
impl fmt::Display for InterruptFrame {
    fn fmt(
        &self,
        f: &mut fmt::Formatter,
    ) -> fmt::Result {
        writeln!(f, "General purpose registers:")?;

        // Print general-purpose registers
        for (i, reg) in self.gp.iter().enumerate() {
            write!(f, "    x{: <#4}: {: >#018X}\n", i, reg)?;
        }

        write!(f, "    elr  : {:#018X}\n", self.elr)?;
        write!(f, "    spsr : {:#018X}\n", self.spsr)?;
        write!(f, "    esr  : {:#018X}\n", self.esr)
    }
}

/// Returns the current exception level as a tuple containing the value and a string representation.
pub fn current_exception_level() -> (CurrentEL::EL::Value, &'static str) {
    let el = CurrentEL.read_as_enum(CurrentEL::EL);
    match el {
        Some(CurrentEL::EL::Value::EL3) => (CurrentEL::EL::Value::EL3, "EL3"),
        Some(CurrentEL::EL::Value::EL2) => (CurrentEL::EL::Value::EL2, "EL2"),
        Some(CurrentEL::EL::Value::EL1) => (CurrentEL::EL::Value::EL1, "EL1"),
        Some(CurrentEL::EL::Value::EL0) => (CurrentEL::EL::Value::EL0, "EL0"),
        _ => (CurrentEL::EL::Value::EL0, "Unknown"),
    }
}

/// Initializes the exception vector table.
///
/// This function sets the vector base address register (VBAR_EL2) to point to the
/// exception vector table and ensures the update is complete before continuing.
pub unsafe fn vector_init() {
    extern "Rust" {
        static vectors: UnsafeCell<()>;
    }

    VBAR_EL2.set(vectors.get() as u64);

    barrier::isb(barrier::SY);
}
