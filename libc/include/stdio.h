#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int put_char(int);
int puts(const char*);

void init_stdin();
void stdin_putchar(char);
int stdin_getchar();

#ifdef __cplusplus
}
#endif

#endif
