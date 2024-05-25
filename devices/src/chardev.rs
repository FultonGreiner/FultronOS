extern crate drivers;

use drivers::uart::UART;
use core::fmt::{self, Write};

/// A trait representing a character device, providing methods for initialization,
/// reading, writing, and deinitialization.
pub trait CharDevice {
    fn new() -> Self;
    fn init(&self);
    fn write_byte(
        &self,
        byte: u8,
    );
    fn read_byte(&self) -> u8;
    fn deinit(&self);
}

/// A struct representing a character device such as UART.
pub struct CharDev<T: CharDevice> {
    device: T,
}

impl<T: CharDevice> CharDev<T> {
    /// Creates a new `CharDev` instance.
    ///
    /// # Returns
    ///
    /// A new `CharDev` instance.
    pub fn new() -> Self {
        CharDev { device: T::new() }
    }

    /// Initializes the character device.
    pub fn init(&self) {
        self.device.init();
    }

    /// Writes a byte to the character device.
    ///
    /// # Arguments
    ///
    /// * `byte` - The byte to write to the device.
    pub fn write_byte(
        &self,
        byte: u8,
    ) {
        self.device.write_byte(byte);
    }

    /// Reads a byte from the character device.
    ///
    /// # Returns
    ///
    /// The byte read from the device.
    pub fn read_byte(&self) -> u8 {
        self.device.read_byte()
    }

    /// Deinitializes the character device.
    pub fn deinit(&self) {
        self.device.deinit();
    }
}

impl<T: CharDevice> Write for CharDev<T> {
    /// Writes a string slice to the character device.
    ///
    /// This method iterates over the bytes in the string slice and writes each byte
    /// to the character device.
    ///
    /// # Arguments
    ///
    /// * `s` - The string slice to write to the device.
    ///
    /// # Returns
    ///
    /// This method returns `fmt::Result`, indicating the success or failure of the write operation.
    fn write_str(
        &mut self,
        s: &str,
    ) -> fmt::Result {
        for byte in s.bytes() {
            self.write_byte(byte);
        }
        Ok(())
    }
}

impl CharDevice for UART {
    fn new() -> Self {
        UART::new()
    }

    fn init(&self) {
        self.init()
    }

    fn write_byte(
        &self,
        byte: u8,
    ) {
        self.write_byte(byte)
    }

    fn read_byte(&self) -> u8 {
        self.read_byte()
    }

    fn deinit(&self) {
        self.deinit()
    }
}
