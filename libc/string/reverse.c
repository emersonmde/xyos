#include <string.h>

void reverse(char *s) {
    size_t i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
