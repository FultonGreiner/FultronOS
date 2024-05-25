#![no_std]
#![no_main]

// extern crate alloc;

use core::fmt::Write;
use cortex_m_rt::entry;
use devices::chardev::CharDev;
use drivers::uart::UART;
use fultronos::vector;

// use blog_os::task::{executor::Executor, keyboard, Task};

mod devices;
mod drivers;
mod panic_handler;

/// Global static variable to hold the UART device instance.
///
/// # Safety
///
/// Access to this variable is unsafe because it is mutable and shared across the entire program.
static mut UART_DEVICE: Option<CharDev<UART>> = None;

/// Macro to print formatted strings to the UART.
///
/// This macro safely accesses the global `UART_DEVICE` variable and writes the formatted string to the UART device.
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

/// Retrieves the current git branch and commit hash.
///
/// This function returns the branch and commit hash as environment variables set by the build script.
fn get_git_info() -> (&'static str, &'static str) {
    (env!("GIT_BRANCH"), env!("GIT_COMMIT"))
}

/// Retrieves the current cargo package version.
///
/// This function returns the cargo package version as an environment variable set by the build script.
fn get_pkg_version() -> &'static str {
    env!("CARGO_PKG_VERSION")
}

const INVALID_ADDR: usize = 0xffffffffffffffff;

/// The main entry point of the program.
///
/// This function initializes the UART device, prints a welcome message with version and git information,
/// and enters an infinite loop to handle UART input and output.
#[entry]
fn kernel_main() -> ! {
    unsafe {
        UART_DEVICE = Some(CharDev::new());
    }

    if let Some(ref mut uart) = unsafe { UART_DEVICE.as_mut() } {
        uart.init();
    } else {
        println!("UART initialization failed");
        loop {}
    }

    // Retrieve and print the git branch, commit hash, and package version
    let (branch, commit) = get_git_info();
    let pkg_version = get_pkg_version();
    let (_, exception_level) = vector::current_exception_level();

    println!("Welcome to FultronOS!");
    println!("Version Info: v{}", pkg_version);
    println!("Branch: {}, Commit: {}", branch, commit);
    println!("Current privilege level: {}", exception_level);

    unsafe {
        vector::enable_irq();
        vector::vector_init();
        vector::disable_irq();
    }

    loop { }
}
