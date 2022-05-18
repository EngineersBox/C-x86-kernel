KERNEL_ASM_PATH = src/asm/kernel.asm
KERNEL_ASM_OBJ = kernel_asm.o
KERNEL_C_PATH = src/core/kernel.c
KERNEL_C_OBJ = kernel_c.o
LINKER_CFG_PATH = linker/linker.ld
KERNEL_ELF_NAME = kernel


.PHONY: clean compile run-unix run-windows

clean:
	rm kernel kernel_asm.o kernel_c.o

compile:
	nasm -f elf32 $(KERNEL_ASM_PATH) -o $(KERNEL_ASM_OBJ)
	gcc -m32 -c $(KERNEL_C_PATH) -o $(KERNEL_C_OBJ)
	ld -m elf_i386 -T $(LINKER_CFG_PATH) -o $(KERNEL_ELF_NAME) $(KERNEL_ASM_OBJ) $(KERNEL_C_OBJ)

run-unix:
	qemu-system-i386 -kernel $(KERNEL_ELF_NAME)

run-windows:
	qemu-system-i386.exe -kernel $(KERNEL_ELF_NAME)

# ==== RUN CONFIGS ==== #

unix: clean compile run-unix

windows: clean compile run-windows