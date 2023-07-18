// declare `_start` globally for access & linking
.global _start

// entry point (code execution begins here)
_start:
    // set stack pointer to top address of stack memory
    ldr sp, =stack_top
    // save return address, branch to `start` subroutine
    bl start

1:
    // unconditional branch to `1` label
    b 1b

// calculate size of `_start` label
.size _start, . - _start
