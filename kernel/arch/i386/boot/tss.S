.globl set_tss
set_tss:
    movw $0x2b, %ax
    ltr %ax
    ret