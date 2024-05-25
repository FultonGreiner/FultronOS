use core::ptr::{read_volatile, write_volatile};

/// Base address of UART0
const UART0_BASE: usize = 0x09000000;

/// Data register for UART0
const UART0_DR: usize = UART0_BASE + 0x00;

/// Flag register for UART0
const UART0_FR: usize = UART0_BASE + 0x18;

/// Receiver FIFO empty flag
const UART_FR_RXFE: u32 = 0x10;

/// A struct representing a low-level UART interface.
pub struct UART;

impl UART {
    /// Creates a new `UART` instance.
    ///
    /// # Returns
    ///
    /// A new `UART` instance.
    pub fn new() -> Self {
        UART
    }

    /// Initializes the UART interface.
    ///
    /// This method sets up the UART hardware for communication, such as setting the baud rate.
    pub fn init(&self) {
        // UART initialization code here (e.g., setting baud rate)
    }

    /// Writes a byte to the UART data register.
    ///
    /// # Arguments
    ///
    /// * `byte` - The byte to write to the UART.
    pub fn write_byte(
        &self,
        byte: u8,
    ) {
        unsafe {
            write_volatile(UART0_DR as *mut u32, byte as u32);
        }
    }

    /// Reads a byte from the UART data register.
    ///
    /// This method blocks until there is data available in the receiver FIFO.
    ///
    /// # Returns
    ///
    /// The byte read from the UART.
    pub fn read_byte(&self) -> u8 {
        // Wait until there is data in the receiver FIFO
        while self.is_receiver_fifo_empty() {}
        unsafe { read_volatile(UART0_DR as *const u32) as u8 }
    }

    /// Checks if the receiver FIFO is empty.
    ///
    /// This method reads the flag register to determine if the receiver FIFO is empty.
    ///
    /// # Returns
    ///
    /// `true` if the receiver FIFO is empty, `false` otherwise.
    pub fn is_receiver_fifo_empty(&self) -> bool {
        unsafe { (read_volatile(UART0_FR as *const u32) & UART_FR_RXFE) != 0 }
    }

    /// De-initializes the UART interface.
    ///
    /// This method performs any necessary cleanup before the UART interface is disabled.
    pub fn deinit(&self) {
        // De-initialize UART if necessary
    }
}
