#include <stdint.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));

void init_page_directory() {
    unsigned int i;
    for (i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }

    uint32_t first_page_table[1024] __attribute__((aligned(4096)));

    for (i = 0; i < 1024; i++) {
        // flags: supervisor level, read+write, present
        first_page_table[i] = (i * 0x1000) | 3;
    }

    // flags: supervisor level, read+write, present
    page_directory[0] = ((unsigned int)first_page_table) | 3;

    asm volatile ("movl %%eax, %%cr3" :: "a" (page_directory));
    asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");
}
