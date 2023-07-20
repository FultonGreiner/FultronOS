TOOLCHAIN_PREFIX = arm-none-eabi-

AS = $(TOOLCHAIN_PREFIX)as
CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld
QEMU = qemu-system-arm

ASFLAGS ?= -march=armv7-a -mcpu=cortex-a15
CCFLAGS ?= -ffreestanding -Wall -Wextra -Werror -nostartfiles
LDFLAGS ?= -T ../kernel/link.ld
QEMUFLAGS ?= -M vexpress-a15 -cpu cortex-a15 -kernel

BINDIR = out
KDIR = kernel

VPATH = $(BINDIR) $(KDIR)

qemu: kernel.elf
	$(QEMU) $(QEMUFLAGS) $(BINDIR)/$< -nographic

# TODO - improve rule to not require `cd` command
kernel.elf: printf.o
	cd $(BINDIR) && $(LD) $(LDFLAGS) _start.o start.o putc.o printf.o -o $@ && cd ..

printf.o: putc.o
	$(CC) $(CCFLAGS) -c $(KDIR)/printf.c -o $(BINDIR)/$@

putc.o: start.o
	$(CC) $(CCFLAGS) -c $(KDIR)/putc.c -o $(BINDIR)/$@

start.o: _start.o
	$(CC) $(CCFLAGS) -c $(KDIR)/start.c -o $(BINDIR)/$@

_start.o: prep_dirs
	$(AS) $(ASFLAGS) -c $(KDIR)/_start.s -o $(BINDIR)/$@

prep_dirs:
	mkdir -p $(BINDIR)

clean:
	$(RM) $(BINDIR)/*.o
	$(RM) $(BINDIR)/*.elf
	$(RM) -rf $(BINDIR)
