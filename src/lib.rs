#![no_std]

extern crate alloc;

#[cfg(target_arch = "aarch64")]
#[path = "arch/aarch64/vector.rs"]
pub mod vector;

pub use vector::{current_exception_level, disable_irq, enable_irq, vector_init};

pub mod allocator;
// pub mod gdt;
// pub mod memory;
// pub mod serial;
pub mod task;
// pub mod vga_buffer;
