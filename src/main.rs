#![no_std]
#![no_main]

use aarch64::vector;
use lib::log_info;
use process::timer;
use smccc::Hvc;
use smccc::psci::system_off;

mod allocator;
mod panic_handler;

#[no_mangle]
fn main() {
    lib::init();
    vector::vector_init();
    timer::timer_init();

    // Retrieve and print the git branch, commit hash, and package version
    let (_, exception_level) = vector::current_exception_level();

    log_info!("Welcome to FultronOS!");
    log_info!("Current privilege level: {}", exception_level);

    system_off::<Hvc>().unwrap();
}
