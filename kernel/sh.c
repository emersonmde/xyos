#include <stdio.h>
#include <arch/i386/tty.h>

void run_sh() {
    printf("\nWelcome to XyOS!\n\n");

    printf("> ");
    stdin_putchar('1');
    stdin_putchar('2');
    stdin_putchar('3');
    for (;;) {
        char c;
        while ((c = stdin_getchar()) != EOF)
            putchar(c);
        // read from stdin
        // buffer current command
        // process command on \n

        // dump stdout
    }
}