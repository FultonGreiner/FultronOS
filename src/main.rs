#![no_std]
#![no_main]

extern crate common;

extern crate aarch64;

// use core::ptr::read_volatile;
use cortex_m_rt::entry;

use aarch64::vector;
use common::log_info;

mod panic_handler;

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
fn main() -> ! {
    common::init();

    // Retrieve and print the git branch, commit hash, and package version
    let (branch, commit) = get_git_info();
    let pkg_version = get_pkg_version();
    let (_, exception_level) = vector::current_exception_level();

    log_info!("Welcome to FultronOS!");
    log_info!("Version Info: v{}", pkg_version);
    log_info!("Branch: {}, Commit: {}", branch, commit);
    log_info!("Current privilege level: {}", exception_level);

    vector::vector_init();

    // Buffer to store incoming UART data
    // let mut buffer: [u8; 128] = [0; 128];
    // let mut idx = 0;

    // log_info!("");
    // log_info!("Trying to read from address 8 GiB...");
    
    // let mut big_addr: u64 = 8 * 1024 * 1024 * 1024;
    // unsafe { read_volatile(big_addr as *mut u64) };

    loop { }
}
