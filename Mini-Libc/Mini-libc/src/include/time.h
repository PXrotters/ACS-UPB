#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern "C" {
#endif

typedef long time_t;

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};


int nanosleep(const struct timespec* req, struct timespec* rem);

#ifdef __cplusplus
}
#endif

#endif
