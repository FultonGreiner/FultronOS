use core::alloc::{GlobalAlloc, Layout};
use core::ptr::null_mut;
use spin::Mutex;

// Define the heap start and size
const HEAP_START: usize = 0x80000;
const HEAP_SIZE: usize = 1024 * 1024; // 1 MiB

struct SimpleAllocator {
    heap_start: usize,
    heap_end: usize,
    next: usize,
}

impl SimpleAllocator {
    const fn new() -> Self {
        SimpleAllocator {
            heap_start: HEAP_START,
            heap_end: HEAP_START + HEAP_SIZE,
            next: HEAP_START,
        }
    }

    unsafe fn alloc(&mut self, layout: Layout) -> *mut u8 {
        let alloc_start = self.next;
        let alloc_end = alloc_start.saturating_add(layout.size());
        if alloc_end > self.heap_end {
            null_mut() // Out of memory
        } else {
            self.next = alloc_end;
            alloc_start as *mut u8
        }
    }

    unsafe fn dealloc(&mut self, _ptr: *mut u8, _layout: Layout) {
        // A simple bump allocator does not support deallocation
    }
}

struct LockedAllocator(Mutex<SimpleAllocator>);

unsafe impl GlobalAlloc for LockedAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let mut allocator = self.0.lock();
        allocator.alloc(layout)
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        let mut allocator = self.0.lock();
        allocator.dealloc(ptr, layout)
    }
}

#[global_allocator]
static ALLOCATOR: LockedAllocator = LockedAllocator(Mutex::new(SimpleAllocator::new()));
