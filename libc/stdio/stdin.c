#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define STDIN_BUF_LEN 5

struct {
    char buf[STDIN_BUF_LEN];
    uint8_t start;
    uint8_t end;
    uint8_t len;
} stdin;

void init_stdin() {
    stdin.start = 0;
    stdin.end = 0;
    stdin.len = 0;
}

void stdin_print_buf() {
    printf("STDIN %d:", stdin.len);
    for (uint8_t i = 0; i < stdin.len; i++)
        putchar(stdin.buf[i]);
    printf("\n");
}

// TODO: length is not being set correctly or being clobbered
void stdin_putchar(char c) {
    stdin.len++;
    stdin.buf[stdin.end++] = c;
    if (stdin.end >= STDIN_BUF_LEN)
        stdin.end = 0;
    if (stdin.len > STDIN_BUF_LEN)
        stdin_getchar();
}

int stdin_getchar() {
    if (stdin.len < 1)
        return EOF;
    stdin.len--;
    char ret = stdin.buf[stdin.start++];
    if (stdin.start >= STDIN_BUF_LEN)
        stdin.start = 0;
    return ret;
}

void stdin_write(const char *s, size_t len) {
    for (size_t i = 0; i < len; i++)
        stdin_putchar(s[i]);
}

void stdin_read(char *s, size_t len) {
    for (size_t i = 0; i < len; i++) {
        char c = stdin_getchar();
        if (c == EOF)
            return;
        s[i] = c;
    }
}