use core::fmt;
use core::fmt::Write;
use spin::Once;

extern crate devices;
extern crate drivers;

use devices::chardev::CharDev;
use drivers::uart::UART;

/// Global static variable to hold the UART device instance.
///
/// # Safety
///
/// Access to this variable is unsafe because it is mutable and shared across the entire program.
static mut UART_DEVICE: Option<CharDev<UART>> = None;

// / Macro to print formatted strings to the UART.
// /
// / This macro safely accesses the global `UART_DEVICE` variable and writes the formatted string to the UART device.
#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => {
        unsafe {
            if let Some(ref mut uart) = UART_DEVICE {
                let _ = write!(uart, $($arg)*);
            }
        }
    };
}

/// Macro to print formatted strings with a newline to the UART.
///
/// This macro safely accesses the global `UART_DEVICE` variable and writes the formatted string followed by a newline to the UART device.
#[macro_export]
macro_rules! println {
    () => (print!("\n"));
    ($fmt:expr) => (print!(concat!($fmt, "\n")));
    ($fmt:expr, $($arg:tt)*) => (print!(concat!($fmt, "\n"), $($arg)*));
}

pub struct Logger;

impl Logger {
    fn new() -> Self {
        Logger
    }

    fn log(&self, level: LogLevel, args: fmt::Arguments) {
        let level_str = match level {
            LogLevel::Info => "INFO",
            LogLevel::Warn => "WARN",
            LogLevel::Error => "ERROR",
            LogLevel::Debug => "DEBUG",
        };
        
        // Handle any unsafe code inside the logger
        print!("{}: ", level_str);
        println!("{}", args);
    }

    fn info(&self, msg: fmt::Arguments) {
        self.log(LogLevel::Info, msg);
    }

    fn warn(&self, msg: fmt::Arguments) {
        self.log(LogLevel::Warn, msg);
    }

    fn error(&self, msg: fmt::Arguments) {
        self.log(LogLevel::Error, msg);
    }

    fn debug(&self, msg: fmt::Arguments) {
        self.log(LogLevel::Debug, msg);
    }
}

enum LogLevel {
    Info,
    Warn,
    Error,
    Debug,
}

static LOGGER: Once<Logger> = Once::new();

pub fn init() {
    unsafe {
        UART_DEVICE = Some(CharDev::new());
    }

    if let Some(ref mut uart) = unsafe { UART_DEVICE.as_mut() } {
        uart.init();
    } else {
        loop {}
    }

    LOGGER.call_once(|| Logger::new());
}

pub fn info(args: fmt::Arguments) {
    if let Some(logger) = LOGGER.get() {
        logger.info(args);
    }
}

pub fn warn(args: fmt::Arguments) {
    if let Some(logger) = LOGGER.get() {
        logger.warn(args);
    }
}

pub fn error(args: fmt::Arguments) {
    if let Some(logger) = LOGGER.get() {
        logger.error(args);
    }
}

pub fn debug(args: fmt::Arguments) {
    if let Some(logger) = LOGGER.get() {
        logger.debug(args);
    }
}
