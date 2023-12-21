#include <stddef.h>
#include <stdint.h>
#include <string.h>

int64_t solution_p1(const char *data, size_t length)
{
    int64_t first = 0, last = 0;
    size_t start, end;
    for (start = 0; start < length; start++) {
        while ((data[start] < '0' || data[start] > '9') && data[start] != '\n' && start < length)
            start++;

        if (data[start] < '0' || data[start] > '9')
            continue;

        first += data[start] - '0';

        for (; data[start] != '\n' && start < length; start++)
            if (data[start] >= '0' && data[start] <= '9')
                end = start;
        last += data[end] - '0';
    }
    return first * 10 + last;
}

int64_t solution_p2(const char *data, size_t length)
{
    return 0;
}
