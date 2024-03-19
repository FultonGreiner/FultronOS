QEMU = qemu-system-arm

QEMUFLAGS ?= -M vexpress-a15 -cpu cortex-a15 -kernel

qemu-i386:
	qemu-system-i386 -nographic -kernel Debug/FultronOS.elf --serial mon:stdio

qemu-riscv:
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel source/arch/riscv64/kernel.elf -serial mon:stdio

qemu:
	$(QEMU) $(QEMUFLAGS) Debug/FultronOS.elf -nographic
