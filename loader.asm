;; Setup stack pointer and launch the kernel
bits 32
section .text
	; multiboot spec
	align	4
	dd	0x1BADB002		; multiboot magic number
	dd	0x00			; flags
	dd	- (0x1BADB002 + 0x00)	; checksum

global load
extern start_kernel

load:
	cli				; clear interrupt flag
	mov	esp,	stack_space	; setup stack space
	call	start_kernel		; launch the kernel
	hlt

section .bss
resb 8192	; 8k stack space
stack_space:
