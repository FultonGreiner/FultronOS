riscv64:
	riscv64-unknown-elf-gcc -Wall -Wextra -c -mcmodel=medany kernel.c -o kernel.o -ffreestanding
	riscv64-unknown-elf-as -c entry.S -o entry.o
	riscv64-unknown-elf-ld -T link.ld -nostdlib kernel.o entry.o -o kernel.elf
