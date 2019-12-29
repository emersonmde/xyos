#include <stdio.h>

#include <arch/i386/tty.h>

#include <arch/i386/io.h>

#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

/* init_pics()
 * init the PICs and remap them
 */
void init_pics(int pic1, int pic2)
{
    /* send ICW1 */
    outb(PIC1, ICW1);
    outb(PIC2, ICW1);

    /* send ICW2 */
    outb(PIC1 + 1, pic1);	/* remap */
    outb(PIC2 + 1, pic2);	/*  pics */

    /* send ICW3 */
    outb(PIC1 + 1, 4);	/* IRQ2 -> connection to slave */
    outb(PIC2 + 1, 2);

    /* send ICW4 */
    outb(PIC1 + 1, ICW4);
    outb(PIC2 + 1, ICW4);

    /* disable all IRQs */
    outb(PIC1 + 1, 0xFF);
}

void init_gdt();
void kernel_main(void) {
	terminal_initialize();
	printf("Terminal Initialized\n");

    printf("Initializing GDT... ");
    init_gdt();
    printf("Done\n");

    printf("Initializing IDT... ");
    idt_init();
    printf("Done\n");

    printf("\nWelcome to XyOS!\n");

    for(;;){}
}
