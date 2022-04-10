#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static bool print(const char *data, size_t length) {
	const unsigned char *bytes = (const unsigned char *) data;
	for (size_t i = 0; i < length; i++)
		if (put_char(bytes[i]) == EOF)
			return false;
	return true;
}

// TODO: BUG: using multiple %d's followed by %s results in buffer overflows and other strange errors
int printf(const char * restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	// TODO: add width/precision support
	while (*format != '\0') {
		size_t remaining = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
		    // treat %% as a single printable '%'
			if (format[0] == '%')
				format++;
			size_t amount = 1;

			// print everything until the next format character
			while (format[amount] && format[amount] != '%')
				amount++;
			if (remaining < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;

			format += amount;
			written += amount;
			continue;
		}

		// consume the format character
		const char *format_start = format++;

		// TODO: Might make more sense to use switch here until precision is added
		if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int);
            if (!remaining) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        } else if (*format == 'd') {
		    // TODO: %d %x and %b can all fall through with separate bases
		    // TODO: s buffer is really fragile, add error checking
            format++;
            // TODO: this int64 is being cast to int (see itoa)
            int64_t d = va_arg(parameters, int64_t);

            char s[512];
            itoa(d, s, 10);
            size_t len = strlen(s);

            if (remaining < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(s, len))
                return -1;
            written++;
        } else if (*format == 'x') {
            // TODO: %d %x and %b can all fall through with separate bases
            // TODO: s buffer is really fragile, add error checking
            format++;
            // TODO: support a larger integer type
            int d = va_arg(parameters, int);

            // TODO: this seems really fragile
            char s[512];
            itoa(d, s, 16);
            size_t len = strlen(s);

            if (remaining < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(s, len))
                return -1;
            written++;
        } else if (*format == 'b') {
            // TODO: %d %x and %b can all fall through with separate bases
            // TODO: s buffer is really fragile, add error checking
            format++;
            // TODO: support a larger integer type
            int d = va_arg(parameters, int);

            // TODO: this seems really fragile
            char s[512];
            itoa(d, s, 2);
            size_t len = strlen(s);

            if (remaining < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(s, len))
                return -1;
            written++;
		} else if (*format == 's') {
            format++;
            const char *str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (remaining < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
		} else {
			format = format_start;
			size_t len = strlen(format);
			if (remaining < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
