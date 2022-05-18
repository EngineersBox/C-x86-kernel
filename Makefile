KERNEL_ASM_PATH = src/asm/kernel.asm
KERNEL_ASM_OBJ = kernel_asm.o
KERNEL_C_PATH = src/core/kernel.c
KERNEL_C_OBJ = kernel_c.o
LINKER_CFG_PATH = linker/linker.ld
KERNEL_ELF_NAME = kernel

LIB32_PATH = /usr/lib32

.PHONY: clean compile run-unix run-windows

clean:
	rm -f kernel kernel_asm.o kernel_c.o

compile:
	nasm -f elf32 $(KERNEL_ASM_PATH) -o $(KERNEL_ASM_OBJ)
	gcc -Wall -m32 -c $(KERNEL_C_PATH) -o $(KERNEL_C_OBJ)
	ld -L$(LIB32_PATH) -m elf_i386 -T $(LINKER_CFG_PATH) -o $(KERNEL_ELF_NAME) $(KERNEL_ASM_OBJ) $(KERNEL_C_OBJ) -lc

run-unix:
	qemu-system-i386 -kernel $(KERNEL_ELF_NAME)

run-windows:
	qemu-system-i386.exe -kernel $(KERNEL_ELF_NAME)

# ==== RUN CONFIGS ==== #

unix: clean compile run-unix

windows: clean compile run-windows