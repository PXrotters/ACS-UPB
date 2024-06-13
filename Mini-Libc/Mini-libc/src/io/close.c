// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	int result = syscall(__NR_close, fd);

    if (result < 0) {
        errno = -result;
        return -1;
    }

    return result;
}
