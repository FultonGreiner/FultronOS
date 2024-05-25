use core::panic::PanicInfo;

extern crate common;

use common::log_error;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    log_error!("{}", _info);
    loop {}
}
