#include <stdio.h>
#include <unistd.h>

int puts(const char *str) {
    const char *str2;
    str2 = str;
    int value = 0;
    while (*str != '\0') {
        value++;
        str++;
    }
    write(1, str2, value);

    write(1, "\n", 1);

    return 0;
}
