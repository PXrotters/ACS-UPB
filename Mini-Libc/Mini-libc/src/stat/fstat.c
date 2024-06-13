// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	int result = syscall(__NR_fstat, fd, st);

    if (result < 0) {
        errno = -result;
        return -1;
    }

    return result;
}
