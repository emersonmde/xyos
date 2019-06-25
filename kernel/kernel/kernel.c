#include <stdio.h>

#include <tty.h>

void kernel_main(void) {
	terminal_initialize();
    printf("testing scolling");
    for (int i = 0; i < 5000; i++)  {
        printf(".");
    }

	printf("\nWelcome to XyOS!\n");
}
