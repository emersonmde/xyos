#include <stdio.h>
#include <arch/i386/tty.h>
#include <arch/i386/io.h>

#include <sh.h>

void init_gdt();
void init_keyboard();

void kernel_main(void) {
	terminal_initialize();
	printf("Terminal Initialized\n");

    printf("Initializing GDT... ");
    init_gdt();
    printf("Done\n");

    printf("Initializing IDT... ");
    idt_init();
    printf("Done\n");

    printf("Initializing Keyboard... ");
    init_keyboard();
    printf("Done\n");

    printf("launching sh...\n");
    run_sh();

    for(;;)
        asm("hlt");
}