#include <stddef.h>
#include <stdint.h>
#include <string.h>

int64_t solution_p1(const char *data, size_t length)
{
    int64_t first = 0, last = 0;
    size_t start, end;
    for (start = 0; start < length; start++) {
        while ((data[start] < '0' || data[start] > '9') &&
               data[start] != '\n' && start < length)
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
#define INDEX(S) (((S)[0] ^ (S)[1]) % 128)
#define ADD_ENTRY(M, S, V)  \
    (M)[INDEX(S)] = (Entry) \
    {                       \
        (S), strlen(S), (V) \
    }

    typedef struct {
        char str[6];
        size_t len;
        int8_t val;
    } Entry;

    Entry map[128] = { 0 };

    ADD_ENTRY(map, "one", 1);
    ADD_ENTRY(map, "two", 2);
    ADD_ENTRY(map, "three", 3);
    ADD_ENTRY(map, "four", 4);
    ADD_ENTRY(map, "five", 5);
    ADD_ENTRY(map, "six", 6);
    ADD_ENTRY(map, "seven", 7);
    ADD_ENTRY(map, "eight", 8);
    ADD_ENTRY(map, "nine", 9);

    int64_t first = 0, last = 0, tmp = 0;
    size_t start, end;
    for (start = 0; start < length; start++) {
        for (; data[start] != '\n' && start < length; start++) {
            if (data[start] >= '0' && data[start] <= '9') {
                first += data[start] - '0';
                goto found;
            }

            Entry *entry = &map[INDEX(&data[start])];
            if (!entry->str[0])
                continue;
            if (start + entry->len >= length)
                continue;
            if (strncmp(entry->str, &data[start], entry->len) == 0) {
                first += entry->val;
                goto found;
            }
        }
        continue;
found:
        for (; data[start] != '\n' && start < length; start++)
            if (data[start] >= '0' && data[start] <= '9')
                end = start;
        tmp = data[end] - '0';

        for (end++; data[end] != '\n' && end < length - 3; end++) {
            Entry *entry = &map[INDEX(&data[end])];
            if (!entry->str[0])
                continue;
            if (end + entry->len >= length)
                continue;
            if (strncmp(entry->str, &data[end], entry->len) == 0)
                tmp = entry->val;
        }
        last += tmp;
    }
    return first * 10 + last;
}
