#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags_limit_high;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_descriptor_t;

typedef struct {
    uint32_t base;
    uint32_t limit;
    uint8_t access;
    uint8_t flags;
} unencoded_gdt_entry_t;

typedef struct {
    uint32_t prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
    uint32_t esp0;       // The stack pointer to load when we change to kernel mode.
    uint32_t ss0;        // The stack segment to load when we change to kernel mode.
    uint32_t esp1;       // everything below here is unusued now.. 
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;         
    uint32_t cs;        
    uint32_t ss;        
    uint32_t ds;        
    uint32_t fs;       
    uint32_t gs;         
    uint32_t ldt;      
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed)) tss_entry_t;

struct {
    gdt_entry_t entries[6];
    gdt_descriptor_t descriptor;
} gdt;

tss_entry_t tss;

void flush_gdt();
void set_gdt(gdt_entry_t *base, uint16_t limit);
void set_tss();

void encode_gdt_entry(gdt_entry_t *target, unencoded_gdt_entry_t source) {
    // Encode 4 flag bits
    // bits 0:4
    target->flags_limit_high = source.flags & 0xF;

    // Encode 20 bit limit
    // bits 0:15
    target->limit_low = source.limit & 0xFFFF;
    // bits 16:19
    target->flags_limit_high = ((source.limit >> 16) & 0xF) | ((source.flags << 4) & 0xF0);

    // Encode 32 bit base
    // bits 0:15
    target->base_low = source.base & 0xFFFF;
    // bits 16:23
    target->base_middle = (source.base >> 16) & 0xFF;
    // bits 24:31
    target->base_high = (source.base >> 24) & 0xFF;

    // Encode access byte
    target->access = source.access;
}

void init_tss() {
    memset(&tss, 0, sizeof(tss));
    
}

void init_gdt() {
    gdt.descriptor.base = (uint32_t)&gdt.entries[0];
    gdt.descriptor.limit = sizeof(gdt.entries) - 1;

    // Creating 4 segments that overlap all 4GB of address space
    // Set null segment
    encode_gdt_entry(&gdt.entries[0], (unencoded_gdt_entry_t){.base=0, .limit=0, .access=0, .flags=0});
    // Set kernel code segment
    encode_gdt_entry(&gdt.entries[1], (unencoded_gdt_entry_t){.base=0, .limit=0xffffffff, .access=0x9A, .flags=0xC});
    // Set kernel data segment
    encode_gdt_entry(&gdt.entries[2], (unencoded_gdt_entry_t){.base=0, .limit=0xffffffff, .access=0x92, .flags=0xC});
    // Set user code segment
    encode_gdt_entry(&gdt.entries[3], (unencoded_gdt_entry_t){.base=0, .limit=0xffffffff, .access=0xFA, .flags=0xC});
    // Set user data segment
    encode_gdt_entry(&gdt.entries[4], (unencoded_gdt_entry_t){.base=0, .limit=0xffffffff, .access=0xF2, .flags=0xC});
    // TODO: Add TSS segment
    encode_gdt_entry(&gdt.entries[5], (unencoded_gdt_entry_t){.base=(uint32_t)&tss, .limit=sizeof(tss), .access=0x89, .flags=0x4});

    tss.ss0 = 0x10;
    tss.esp0 = 0x10;

    set_gdt(gdt.entries, sizeof(gdt.entries));
    set_tss();
    flush_gdt();
}
