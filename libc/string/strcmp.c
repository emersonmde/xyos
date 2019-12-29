#include <string.h>

int strcmp(const char *s1, const char *s2) {
    unsigned char c1, c2;
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;

        // \0 == 0 in ASCII
        if (c1 == '\0' || c2 == '\0')
            return c1 - c2;
    } while(c1 == c2);

    return c1 - c2;
}
