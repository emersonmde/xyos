/*
 * kernel.c
 *
 * Copyright (c) 2018 Matthew Emerson
 */

#include <kernel.h>

void clear_screen(void) {
	// Clear the screen
	// 80 chars wide, 25 chars high, 2 bytes per char
	volatile char *video = (volatile char *)0xB8000;
	for(int i = 0; i < SCR_HEIGHT * SCR_WIDTH * 2; i += 2) {
		*video++ = ' ';
		*video++ = TEXT_COLOR;
	}
}

void init_screen(void) {
	screen.x = 0;
	screen.y = 0;
	clear_screen();
}


void scroll(int lines) {
	volatile char *video = (volatile char *)0xB8000;
	for(int i = 0; i < SCR_WIDTH * SCR_HEIGHT * 2; i++) {
		*video = *(video + SCR_WIDTH * 2);
		video++;
	}
	screen.x = 0;
	screen.y = SCR_HEIGHT - 2;
}

void put_char(char c) {
	volatile char *video = (volatile char *)0xB8000;
	int cursor_pos = (screen.x * 2) + (screen.y * SCR_WIDTH * 2);
	*(video + cursor_pos) = c;
	*(video + cursor_pos + 1) = TEXT_COLOR;
	if(screen.x >= SCR_WIDTH - 1) {
		screen.x = 0;
		screen.y++;
		if(screen.y >= SCR_HEIGHT) {
			screen.y = SCR_HEIGHT;
			scroll(1);
		}
	} else {
		screen.x++;
	}
}

void put_string(const char *s) {
	while( *s != '\0' ) {
		put_char(*s++);
	}
}

void print_string(const char *s) {
	volatile char *video = (volatile char *)0xB8000;
	while( *s != '\0' ) {
		*video++ = *s++;
		*video++ = TEXT_COLOR;
	}
}

void start_kernel(void) {
	init_screen();

	const char *str = "Welcome to XyOS adf asdf sdf";
	for(int i = 0; i < 80; i++) {
		put_string(str);
	}

	const char *asdf = "last line";
	put_string(asdf);

	for(;;)

	return;
}
