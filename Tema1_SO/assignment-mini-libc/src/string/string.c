// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	size_t i = 0;

	if (destination == NULL) {
		return NULL;
	}

	while (source[i] != '\0') {
		destination[i] = source[i];
		i++;
	}

	destination[i] = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t i = 0;

    if (destination == NULL) {
        return NULL;
    }

    while (i < len && source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }

    while (i < len) {
        destination[i] = '\0';
        i++;
    }

    return destination;
}

char *strcat(char *destination, const char *source)
{
	int i = 0, j = 0;

	while (destination[i] != '\0') {
		i++;
	}

	while (source[j] != '\0') {
		destination[i] = source[j];
		i++;
		j++;
	}

	destination[i] = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	size_t dest_len = strlen(destination);
    size_t i = 0;
    char *dest = destination + dest_len;

    while (i < len && source[i] != '\0') {
        dest[i] = source[i];
        i++;
    }

    dest[i] = '\0';
    return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    while (len > 0 && *str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
        len--;
    }

    if (len == 0 || (*str1 == '\0' && *str2 == '\0')) {
        return 0;
    } else if (*str1 > *str2) {
        return 1;
    } else {
        return -1;
    }
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	while (*str != '\0') {
		if (*str == c) {
			return (char *) str;
		}

		str++;
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	char *appearance = NULL;

    while (*str != '\0') {
        if (*str == c) {
            appearance = (char *) str;
        }

        str++;
    }

    if (c == '\0') {
        return (char *) str;
    }

    return appearance;
}

char *strstr(const char *haystack, const char *needle)
{
	if (*needle == '\0') {
        return (char *) haystack;
    }

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *) haystack;
        }

        haystack++;
    }

    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	if (*needle == '\0') {
        return (char *) haystack;
    }

    const char *appearance = NULL;

    while (*haystack != '\0') {
        const char *hay = haystack;
        const char *need = needle;

        while (*hay != '\0' && *need != '\0' && *hay == *need) {
            hay++;
            need++;
        }

        if (*need == '\0') {
            appearance = haystack;
        }

        haystack++;
    }

    if (appearance != NULL) {
        return (char *) appearance;
    }

    return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	if (destination == NULL) {
		return NULL;
	}

	char *dest = (char *) destination;
	char *src = (char *) source;

	for (size_t i = 0; i < num; i++) {
		dest[i] = src[i];
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	if (destination == NULL || source == NULL) {
        return NULL;
    }

    char *dest = (char *) destination;
    const char *src = (const char *) source;

    if (dest > src && dest < src + num) {
        for (size_t i = num - 1; i < num; i--) {
            dest[i] = src[i];
        }

    } else {
        for (size_t i = 0; i < num; i++) {
            dest[i] = src[i];
        }
    }

    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *p1 = (const unsigned char *) ptr1;
    const unsigned char *p2 = (const unsigned char *) ptr2;

    for (size_t i = 0; i < num; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }

    return 0;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char *p = (unsigned char *)source;
    unsigned char val = (unsigned char)value;

    for (size_t i = 0; i < num; i++) {
        p[i] = val;
    }

    return source;
}
