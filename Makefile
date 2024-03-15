TOOLCHAIN_PREFIX = arm-none-eabi-

AS = $(TOOLCHAIN_PREFIX)as
CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld
OBJCOPY = $(TOOLCHAIN_PREFIX)objcopy

# ASFLAGS ?= -mcpu=cortex-a8 -march=armv7-a+vfpv3-d16-fp16
CCFLAGS ?= -ffreestanding -Wall -Wextra -Werror -nostartfiles -nostdlib -fno-builtin -fno-stack-protector -mcpu=cortex-a8 -mfpu=neon-vfpv3 -mfloat-abi=softfp -mthumb 
CCFLAGS += -nostdlib

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILDDIR = $(ROOT_DIR)/build
BINDIR = $(BUILDDIR)/bin

LDFLAGS ?= -T $(ROOT_DIR)/memmap.ld

QEMU = qemu-system-arm
QEMUFLAGS ?= -M vexpress-a15 -cpu cortex-a15 -kernel

KDIR = $(ROOT_DIR)/kernel
STARTUPDIR = $(KDIR)/startup

LIBDIR = $(ROOT_DIR)/lib

TFTPDIR = /tftp

VPATH = $(BINDIR) $(KDIR)

TARGET_BIN = $(BINDIR)/kernel.bin
TARGET_ELF = $(BINDIR)/kernel.elf

qemu:
	$(QEMU) $(QEMUFLAGS) Debug/FultronOS.elf -nographic

copy:
	cp $(TARGET_BIN) $(TFTPDIR)

kernel: libc
	cd $(BINDIR) &&  $(CC) $(CCFLAGS) $(LDFLAGS) -o $@.elf _start.o start.o putc.o printf.o -lc -lgcc -lm && cd ..
	$(OBJCOPY) $(TARGET_ELF) $(TARGET_BIN) -O binary

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
