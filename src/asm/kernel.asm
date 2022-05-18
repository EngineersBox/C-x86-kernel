bits 32  ; NASM directive to mark as 32 bit
section .text ; Code declaration section
    ; Multiboot spec
    align 4
    dd 0x1BADB002 ; Magic bytes, required for PVH (paravirtualisation of hardware virtual machines) guests
    dd 0x00 ; Flags
    dd - (0x1BADB002 + 0x00) ; Checksum

global start ; Load symbols from kernel as globals
extern kernelMain ; Load kernalMain method from compiled C file

start:
    cli ; Clear interrupts to diable interrupts
    mov esp, stack_space ; Set stack pointer to empty stack_space label
    call kernelMain ; Invoke referenced kernelMain function
    hlt ; Halts the CPU

section .bss ; Block starting symbol for statically allocated vars
resb 8192 ; Reserve 8KB of memory for stack
stack_space: