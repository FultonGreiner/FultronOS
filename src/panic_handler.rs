use core::panic::PanicInfo;

use lib::log_error;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    log_error!("{}", _info);
    loop {}
}
