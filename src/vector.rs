#[cfg(target_arch = "aarch64")]
#[path = "arch/aarch64/vector.rs"]
mod vector;

pub use vector::{current_exception_level, vector_init};
