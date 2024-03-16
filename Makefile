TOOLCHAIN_PREFIX = arm-none-eabi-

AS = $(TOOLCHAIN_PREFIX)as
CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld
QEMU = qemu-system-arm

# -march=armv7-a+vfpv3-d16-fp16
ASFLAGS ?= -mcpu=cortex-a8 -march=armv7-a+vfpv3-d16-fp16
# -mfpu=neon-vfpv3 -mfloat-abi=softfp
CCFLAGS ?= -ffreestanding -Wall -Wextra -Werror -nostartfiles -nostdlib -fno-builtin -fno-stack-protector -mcpu=cortex-a8 -mfpu=neon-vfpv3 -mfloat-abi=softfp -mthumb

LDFLAGS ?= -T ../kernel/link.ld
QEMUFLAGS ?= -M vexpress-a9 -cpu cortex-a9 -s -S -kernel

BINDIR = out
KDIR = kernel

# LIBG = $(shell $(CC) -print-file-name=libg.a)
# LIBM = $(shell $(CC) -print-file-name=libm.a)
# LIBGCC = $(shell $(CC) -print-libgcc-file-name)

LIBG = /opt/homebrew/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/bin/../lib/gcc/arm-none-eabi/10.3.1/../../../../arm-none-eabi/lib/
LIBM = /opt/homebrew/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/bin/../lib/gcc/arm-none-eabi/10.3.1/../../../../arm-none-eabi/lib/
LIBGCC = /opt/homebrew/Cellar/arm-none-eabi-gcc/10.3-2021.07/gcc/bin/../lib/gcc/arm-none-eabi/10.3.1/

VPATH = $(BINDIR) $(KDIR)

qemu:
	$(QEMU) $(QEMUFLAGS) Debug/FultronOS.elf -nographic

# TODO - improve rule to not require `cd` command
# kernel.elf: printf.o
# 	cd $(BINDIR) &&  $(CC) $(CCFLAGS) $(LDFLAGS) -o $@ -ffreestanding _start.o start.o putc.o printf.o -lgcc -lm -lg && cd ..
# 	# cd $(BINDIR) && $(CC) $(CCFLAGS) $(LDFLAGS) _start.o start.o putc.o printf.o -o $@ -L$(LIBGCC) -lgcc -L$(LIBM) -lm -L$(LIBG) -lg && cd ..

printf.o: putc.o
	$(CC) $(CCFLAGS) -c $(KDIR)/printf.c -o $(BINDIR)/$@

putc.o: start.o
	$(CC) $(CCFLAGS) -c $(KDIR)/putc.c -o $(BINDIR)/$@

start.o: _start.o
	$(CC) $(CCFLAGS) -fPIC -c $(KDIR)/start.c -o $(BINDIR)/$@

_start.o: prep_dirs
	$(AS) $(ASFLAGS) -c $(KDIR)/_start.s -o $(BINDIR)/$@

prep_dirs:
	mkdir -p $(BINDIR)

clean:
	$(RM) $(BINDIR)/*.o
	$(RM) $(BINDIR)/*.elf
	$(RM) -rf $(BINDIR)
