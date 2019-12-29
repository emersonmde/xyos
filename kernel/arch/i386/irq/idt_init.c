#include <stdint.h>
#include <arch/i386/io.h>

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

static struct {
    idt_entry_t entries[256];
} idt;

typedef struct {
    uint32_t offset;
    uint16_t selector;
    uint8_t type;
} unencoded_idt_entry_t;

struct IDT_entry{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[256];

// ASM from irq.S
extern void load_idt();
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void remap_pic() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void encode_idt_entry(idt_entry_t *target, unencoded_idt_entry_t source) {
    target->offset_low = source.offset & 0xffff;
    target->offset_high = (source.offset & 0xffff0000) >> 16;
    target->selector = source.selector;
    target->type_attr = source.type;
    target->zero = 0;
}

void idt_init(void) {
    uint32_t idt_address;
    uint32_t idt_ptr[2];

    // the PIC needs to be remapped before loading the IDT
    remap_pic();

    uint32_t irqs[] = {
        (uint32_t)&irq0,
        (uint32_t)&irq1,
        (uint32_t)&irq2,
        (uint32_t)&irq3,
        (uint32_t)&irq4,
        (uint32_t)&irq5,
        (uint32_t)&irq6,
        (uint32_t)&irq7,
        (uint32_t)&irq8,
        (uint32_t)&irq9,
        (uint32_t)&irq10,
        (uint32_t)&irq11,
        (uint32_t)&irq12,
        (uint32_t)&irq13,
        (uint32_t)&irq14,
        (uint32_t)&irq15,
    };

    for (int i = 0; i < 15; i++) {
        encode_idt_entry(&idt.entries[i + 32], (unencoded_idt_entry_t){.offset=irqs[i], .selector=0x08, .type=0x8e});
    }

    // TODO: add descriptor to idt struct in favor of idt_address/idt_ptr
    // format idt descriptor
    idt_address = (uint32_t)&idt.entries ;
    idt_ptr[0] = (sizeof(idt_entry_t) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16 ;

    // profit
    load_idt(idt_ptr);
}