#include <stdlib.h>
#include <string.h>

#include "input.h"

char *read_line(FILE *stream)
{
    size_t buffer_size = 1024, buffer_length = 0;
    char *buffer = malloc(buffer_size);

    if (!buffer)
        goto error_alloc;

    while (1) {
        fgets(buffer + buffer_length, buffer_size - buffer_length, stream);
        if (ferror(stdin) || feof(stdin))
            goto error_io_free;
        buffer_length += strlen(buffer + buffer_length);
        if (buffer[buffer_length - 1] != '\n') {
            buffer_size *= 2;
            char *temp = realloc(buffer, buffer_size);
            if (!temp)
                goto error_alloc_free;
            buffer = temp;
        } else {
            buffer[buffer_length - 1] = '\0';
            return buffer;
        }
    }

    errno = 0;
    return buffer;

error_io_free:
    free(buffer);
    errno = EIO;
    return NULL;

error_alloc_free:
    free(buffer);
error_alloc:
    errno = ENOMEM;
    return NULL;
}

unsigned long long read_ull(FILE *stream)
{
    char *buffer = read_line(stdin);
    if (errno)
        return -1;

    size_t len = strcspn(buffer, " \t\r\n");
    if (len == 0)
        goto error_invalid;
    buffer[len] = '\0';

    char *error;
    unsigned long long num = strtoull(buffer, &error, 10);
    if (*error)
        goto error_invalid;

    free(buffer);
    errno = 0;
    return num;

error_invalid:
    free(buffer);
    errno = EINVAL;
    return -1;
}

long read_long(FILE *stream)
{
    char *buffer = read_line(stdin);
    if (errno)
        return -1;

    size_t len = strcspn(buffer, " \t\r\n");
    if (len == 0)
        goto error_invalid;
    buffer[len] = '\0';

    char *error;
    long num = strtol(buffer, &error, 10);
    if (*error)
        goto error_invalid;

    free(buffer);
    errno = 0;
    return num;

error_invalid:
    free(buffer);
    errno = EINVAL;
    return -1;
}

unsigned long long string_to_ull(const char *string)
{
    char *error;

    size_t len = strcspn(string, " \t\r\n");
    if (len == 0)
        goto error_invalid;

    unsigned long long num = strtol(string, &error, 10);
    if (error != string + len)
        goto error_invalid;

    return num;

error_invalid:
    errno = EINVAL;
    return -1;
}

long string_to_long(const char *string)
{
    char *error;

    size_t len = strcspn(string, " \t\r\n");
    if (len == 0)
        goto error_invalid;

    long num = strtol(string, &error, 10);
    if (error != string + len)
        goto error_invalid;

    return num;

error_invalid:
    errno = EINVAL;
    return -1;
}
