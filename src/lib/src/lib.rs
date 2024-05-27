#![no_std]

pub mod logger;

pub use logger::{init, info, warn, error, debug};

#[macro_export]
macro_rules! log_info {
    ($($arg:tt)*) => (lib::info(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! log_warn {
    ($($arg:tt)*) => (lib::warn(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! log_error {
    ($($arg:tt)*) => (lib::error(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! log_debug {
    ($($arg:tt)*) => (lib::debug(format_args!($($arg)*)));
}