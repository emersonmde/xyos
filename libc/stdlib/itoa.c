#include <string.h>
#include <stdio.h>

// TODO: need to support larger integer types for %x and %b but allow signed for %d
void itoa(int n, char *s, int base) {
    int i;
    int sign = 0;
    char *charset = "0123456789ABCDEF";

    if (n < 0) {
        sign = 1;
        n = -n;
    }

    i = 0;
    do {
        s[i++] = charset[n % base];
        n /= base;
    } while(n);

    if (sign)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}
