TOOLCHAIN_PREFIX = arm-none-eabi-

AS = $(TOOLCHAIN_PREFIX)as
CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld

ASFLAGS ?= -mcpu=cortex-a8 -march=armv7-a+vfpv3-d16-fp16

CCFLAGS ?= -ffreestanding -Wall -Wextra -Werror -nostartfiles -nostdlib -fno-builtin -fno-stack-protector -mcpu=cortex-a8 -mfpu=neon-vfpv3 -mfloat-abi=softfp -mthumb

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

LDFLAGS ?= -T $(ROOT_DIR)/link.ld

QEMU = qemu-system-arm
QEMUFLAGS ?= -M vexpress-a15 -cpu cortex-a15 -kernel

BUILDDIR = $(ROOT_DIR)/build
BINDIR = $(BUILDDIR)/bin

KDIR = $(ROOT_DIR)/kernel
STARTUPDIR = $(KDIR)/startup

LIBDIR = $(ROOT_DIR)/lib

VPATH = $(BINDIR) $(KDIR)

qemu: kernel.elf
	$(QEMU) $(QEMUFLAGS) $(BINDIR)/$< -nographic

kernel.elf: libc
	cd $(BINDIR) &&  $(CC) $(CCFLAGS) $(LDFLAGS) -o $@ _start.o start.o putc.o printf.o -lc -lgcc -lm && cd ..

libc: start.o
	$(MAKE) -C $(LIBDIR) libc

start.o: _start.o
	$(CC) $(CCFLAGS) -fPIC -c $(KDIR)/start.c -o $(BINDIR)/$@

_start.o: prep_dirs
	$(AS) $(ASFLAGS) -c $(STARTUPDIR)/_start.s -o $(BINDIR)/$@

prep_dirs:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BINDIR)

clean:
	$(RM) -rf $(BUILDDIR)
