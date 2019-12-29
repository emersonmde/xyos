#include <arch/i386/io.h>
#include <stdio.h>
#include <stdint.h>

// Each of these has to send EOI outb(0x20, 0x20)
// Programmable Interrupt Timer Interrupt
void irq0_handler() {
    outb(0x20, 0x20);
}

// TODO: allow driver to set interrupt handler
// Keyboard Interrupt
void irq1_handler() {
    uint8_t scancode = inb(0x60);
    // j down = 33 = 21
    // j up == 161 = A1
    extern process_scancode(uint8_t);
    process_scancode(scancode);
    outb(0x20, 0x20);
}

// Cascade (used internally by the two PICs. never raised)
void irq2_handler() {
    printf("irq2\n");
    outb(0x20, 0x20);
}

// COM2 (if enabled)
void irq3_handler() {
    printf("irq3\n");
    outb(0x20, 0x20);
}

// COM1 (if enabled)
void irq4_handler() {
    printf("irq4\n");
    outb(0x20, 0x20);
}

// LPT2 (if enabled)
void irq5_handler() {
    printf("irq5\n");
    outb(0x20, 0x20);
}

// Floppy Disk
void irq6_handler() {
    printf("irq6\n");
    outb(0x20, 0x20);
}

// LPT1 / Unreliable "spurious" interrupt (usually)
void irq7_handler() {
    printf("irq7\n");
    outb(0x20, 0x20);
}

// CMOS real-time clock (if enabled)
void irq8_handler() {
    printf("irq8\n");
    outb(0x20, 0x20);
}

// Free for peripherals / legacy SCSI / NIC
void irq9_handler() {
    printf("irq9\n");
    outb(0x20, 0x20);
}

// Free for peripherals / SCSI / NIC
void irq10_handler() {
    printf("irq10\n");
    outb(0x20, 0x20);
}

// Free for peripherals / SCSI / NIC
void irq11_handler() {
    printf("irq11\n");
    outb(0x20, 0x20);
}

// PS2 Mouse
void irq12_handler() {
    printf("irq12\n");
    outb(0x20, 0x20);
}

// FPU / Coprocessor / Inter-processor
void irq13_handler() {
    printf("irq13\n");
    outb(0x20, 0x20);
}

// Primary ATA Hard Disk
void irq14_handler() {
    printf("irq14\n");
    outb(0x20, 0x20);
}

// Secondary ATA Hard Disk
void irq15_handler() {
    printf("irq15\n");
    outb(0x20, 0x20);
}
