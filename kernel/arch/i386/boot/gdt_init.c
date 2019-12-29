#include <stdint.h>
#include <stdio.h>

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

struct {
    gdt_entry_t entries[5];
    gdt_descriptor_t descriptor;
} gdt;

void flush_gdt();
void set_gdt(gdt_entry_t *base, uint16_t limit);

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
    // TODO: Add TSS segment
    // Set user code segment
    encode_gdt_entry(&gdt.entries[3], (unencoded_gdt_entry_t){.base=0, .limit=0xffffffff, .access=0xFA, .flags=0xC});
    // Set user data segment
    encode_gdt_entry(&gdt.entries[4], (unencoded_gdt_entry_t){.base=0, .limit=0xffffffff, .access=0xF2, .flags=0xC});

    set_gdt(gdt.entries, sizeof(gdt.entries));
    flush_gdt();
}
