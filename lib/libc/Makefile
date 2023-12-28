TOOLCHAIN_PREFIX = arm-none-eabi-

CC = $(TOOLCHAIN_PREFIX)gcc

CCFLAGS ?= -ffreestanding -Wall -Wextra -Werror -nostartfiles -nostdlib -fno-builtin -fno-stack-protector -mcpu=cortex-a8 -mfpu=neon-vfpv3 -mfloat-abi=softfp -mthumb

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
STDIO_SRC = $(ROOT_DIR)/stdio/src

BUILDDIR = $(ROOT_DIR)/../../build
BINDIR = $(BUILDDIR)/bin

all: printf.o

printf.o: putc.o
	$(CC) $(CCFLAGS) -c $(STDIO_SRC)/printf.c -o $(BINDIR)/$@

putc.o:
	$(CC) $(CCFLAGS) -c $(STDIO_SRC)/putc.c -o $(BINDIR)/$@
