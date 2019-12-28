gdtr:
limit:	.word	0
base:	.long	0

.globl set_gdt
set_gdt:
	movl 4(%esp), %eax
	movl %eax, (base)
	movw 8(%esp), %ax
	movw %ax, (limit)
	lgdt (gdtr)
	ret

.globl flush_gdt
flush_gdt:
	ljmp $0x08, $complete_flush

complete_flush:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ret
