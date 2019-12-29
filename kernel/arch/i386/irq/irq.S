.globl irq0
irq0:
    pusha
    call irq0_handler
    popa
    iret

.globl irq1
irq1:
    pusha
    call irq1_handler
    popa
    iret

.globl irq2
irq2:
    pusha
    call irq2_handler
    popa
    iret

.globl irq3
irq3:
    pusha
    call irq3_handler
    popa
    iret

.globl irq4
irq4:
    pusha
    call irq4_handler
    popa
    iret

.globl irq5
irq5:
    pusha
    call irq5_handler
    popa
    iret

.globl irq6
irq6:
    pusha
    call irq6_handler
    popa
    iret

.globl irq7
irq7:
    pusha
    call irq7_handler
    popa
    iret

.globl irq8
irq8:
    pusha
    call irq8_handler
    popa
    iret

.globl irq9
irq9:
    pusha
    call irq9_handler
    popa
    iret

.globl irq10
irq10:
    pusha
    call irq10_handler
    popa
    iret

.globl irq11
irq11:
    pusha
    call irq11_handler
    popa
    iret

.globl irq12
irq12:
    pusha
    call irq12_handler
    popa
    iret

.globl irq13
irq13:
    pusha
    call irq13_handler
    popa
    iret

.globl irq14
irq14:
    pusha
    call irq14_handler
    popa
    iret

.globl irq15
irq15:
    pusha
    call irq15_handler
    popa
    iret

.globl load_idt
load_idt:
	movl 4(%esp), %edx
	lidt (%edx)
	sti
	ret
