#ifndef INPUT_H
#define INPUT_H

#include <errno.h>
#include <stdio.h>

/*
 * Read a line from input stream
 *
 * @param   stream      Input stream.
 * @return  Read string.
 *          Writes error to `errno`.
 *          Possible error codes:
 *              ENOMEM - Memory allocation error
 *              EIO - Error reading from input stream
 */
char *read_line(FILE *stream);

/*
 * Reads a long from the input stream.
 *
 * @param   stream      Input stream.
 * @return  Converted number.
 *          Writes error to `errno`.
 *          Possible error codes:
 *              ENOMEM - Memory allocation error
 *              EIO - Error reading from input stream
 *              EINVAL - Input not a number
 */
long read_long(FILE *stream);

/*
 * Converts string to long.
 *
 * @param   string     Input string.
 * @return  Converted number.
 *          Writes error to `errno`.
 *          Possible error codes:
 *              EINVAL - Input not a number
 */
long string_to_long(const char *string);

/*
 * Reads an unsigned long long from the input stream.
 *
 * @param   stream      Input stream.
 * @return  Converted number.
 *          Writes error to `errno`.
 *          Possible error codes:
 *              ENOMEM - Memory allocation error
 *              EIO - Error reading from input stream
 *              EINVAL - Input not a number
 */
unsigned long long read_ull(FILE *stream);

/*
 * Converts string to unsigned long long.
 *
 * @param   string     Input string.
 * @return  Converted number.
 *          Writes error to `errno`.
 *          Possible error codes:
 *              EINVAL - Input not a number
 */
unsigned long long string_to_ull(const char *string);

#endif
