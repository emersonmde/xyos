#ifndef KERNEL_H
#define KERNEL_H

// Location of video memory
#define	VIDEO_MEM	0xB8000

// Screen dimensions
#define	SCR_WIDTH	80
#define	SCR_HEIGHT	25

// Default OS text color
#define	TEXT_COLOR	0x02

struct _screen {
	int x;
	int y;
} screen;

void clear_screen(void);

void init_screen(void);

void put_char(char c);

void put_string(const char *s);

#endif /* KERNEL_H */
