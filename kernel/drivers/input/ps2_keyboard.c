
#include <stdio.h>
#include <arch/i386/io.h>
#include <arch/i386/tty.h>
#include <stdlib.h>
#include <stdbool.h>

#define PS2_COMMAND         0x64
#define PS2_DATA            0x60

// Bit 0 of the status register must be SET before attempting to read data from port 0x60
// Bit 1 of the status register must be CLEAR before attempting to write data to port 0x60
#define WAIT_FOR_READ()   while ((inb(PS2_COMMAND) & 1u) == 0u) asm volatile("rep nop");
#define WAIT_FOR_WRITE()  while ((inb(PS2_COMMAND) & 2u) != 0u) asm volatile("rep nop");

// 0x1D left control
// 0x2A left shift
// 0x36 right shift
// 0x38 left alt
// 0x3A caps lock

unsigned char us_qwerty[128] = {
        0, 27, 49, 50, 51, 52, 53, 54,
        55, 56, 57, 48, 45, 61, 8, 9,
        113, 119, 101, 114, 116, 121, 117, 105,
        111, 112, 91, 93, 10, 0, 97, 115,
        100, 102, 103, 104, 106, 107, 108, 59,
        39, 96, 0, 92, 122, 120, 99, 118,
        98, 110, 109, 44, 46, 47, 0, 0,
        0, 32, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
};

struct {
    bool ctrl;
    bool alt;
    bool shift;
    bool capslock;
} ps2_kbd_state_t;

// https://wiki.osdev.org/%228042%22_PS/2_Controller#Initialising_the_PS.2F2_Controller
void init_keyboard() {
}

void process_scancode(uint8_t scancode) {
    if (scancode & 0x80) {
        // key released
    } else {
        // key pressed
        stdin_putchar(us_qwerty[scancode]);
        //printf("%c", us_qwerty[scancode]);
    }
}