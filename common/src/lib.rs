#![no_std]

pub mod logger;

pub use logger::{init, info, warn, error, debug};

#[macro_export]
macro_rules! log_info {
    ($($arg:tt)*) => (common::info(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! log_warn {
    ($($arg:tt)*) => (common::warn(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! log_error {
    ($($arg:tt)*) => (common::error(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! log_debug {
    ($($arg:tt)*) => (common::debug(format_args!($($arg)*)));
}
