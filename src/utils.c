#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

/*
 * Exits process with error.
 *
 * @param   message     Error message.
 */
void die(const char *message)
{
    fprintf(stderr, "ERROR: %s\n", message);
    exit(EXIT_FAILURE);
}

/*
 * Get time in nanoseconds.
 *
 * @return  Current time in nanoseconds.
 */
int64_t gettime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)ts.tv_sec * 1000000000 + (int64_t)ts.tv_nsec;
}
