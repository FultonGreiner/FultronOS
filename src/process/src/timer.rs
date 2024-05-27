use arm_gic::{irq_enable, wfi};
use arm_gic::gicv3::{GicV3, IntId, Trigger};
use drivers::pl031::Rtc;
// use lib::logger::info;

/// Base addresses of the GICv3.
const GICD_BASE_ADDRESS: *mut u64 = 0x800_0000 as _;
const GICR_BASE_ADDRESS: *mut u64 = 0x80A_0000 as _;

/// Base address of the PL031 RTC.
const PL031_BASE_ADDRESS: *mut u32 = 0x901_0000 as _;
/// The IRQ used by the PL031 RTC.
const PL031_IRQ: IntId = IntId::spi(2);

pub fn timer_init() {
    let mut gic = unsafe {GicV3::new(GICD_BASE_ADDRESS, GICR_BASE_ADDRESS)};
    gic.setup();

    let mut rtc = unsafe { Rtc::new(PL031_BASE_ADDRESS) };
    let timestamp = rtc.read();

    GicV3::set_priority_mask(0xff);
    gic.set_interrupt_priority(PL031_IRQ, 0x00);
    gic.set_trigger(PL031_IRQ, Trigger::Edge);
    gic.enable_all_interrupts(true);

    irq_enable();

    // Wait another 3 seconds for an interrupt.
    let target = timestamp + 3;

    rtc.set_match(target);
    rtc.clear_interrupt();
    rtc.enable_interrupt(true);

    while !rtc.interrupt_pending() {
        wfi();
    }
}