#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/*
 * Checks if path with mode `mode` exists.
 *
 * @param   path        Path to be checked.
 * @param   mode        Mode (for example: S_IFDIR (directory) or S_IFREG (regular file)).
 */
#define PATH_EXISTS(path, mode)                                  \
    ({                                                           \
        struct stat st;                                          \
        stat(path, &st) == 0 && ((st.st_mode & S_IFMT) == mode); \
    })

/*
 * Die and print error message on error.
 */
#define CHECK_ERROR(error)                            \
    switch (error) {                                  \
        case ENOMEM:                                  \
            die("Memory allocation failed.");         \
            break;                                    \
        case EIO:                                     \
            die("Reading from input stream failed."); \
            break;                                    \
        case EINVAL:                                  \
            die("Input not a number.");               \
            break;                                    \
        default:                                      \
            break;                                    \
    }

/*
 * Exits process with error.
 *
 * @param   message     Error message.
 */
void die(const char *message);

/*
 * Get time in nanoseconds.
 *
 * @return  Current time in nanoseconds.
 */
int64_t gettime();

#endif
