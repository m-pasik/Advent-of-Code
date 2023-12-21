#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

bool strnmatch(const char *restrict s1, const char *restrict s2, size_t n)
{
    for (size_t i = 0; s1[i] != '\0' && i < n; i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}

#define INDEX(S) (((S)[0] << 8) | (S)[1])
#define ADD_ENTRY(M, S, V) \
    (M)[INDEX(S)] = (Entry) { (S), (V) }

typedef struct {
    char str[6];
    int8_t val;
} Entry;

int64_t solution_p2(const char *data, size_t length)
{
    Entry lut[256 * 256] = { 0 };

    ADD_ENTRY(lut, "one", 1);
    ADD_ENTRY(lut, "two", 2);
    ADD_ENTRY(lut, "three", 3);
    ADD_ENTRY(lut, "four", 4);
    ADD_ENTRY(lut, "five", 5);
    ADD_ENTRY(lut, "six", 6);
    ADD_ENTRY(lut, "seven", 7);
    ADD_ENTRY(lut, "eight", 8);
    ADD_ENTRY(lut, "nine", 9);

    int64_t first = 0, last = 0, tmp = 0;
    size_t start, end;
    for (start = 0; start < length; start++) {
        for (; data[start] != '\n' && start < length; start++) {
            if (data[start] >= '0' && data[start] <= '9') {
                first += data[start] - '0';
                goto found;
            }

            Entry *entry = lut + INDEX(data + start);
            if (!entry->str[0])
                continue;
            if (strnmatch(entry->str + 2, data + start + 2, length - start - 2)) {
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
            Entry *entry = lut + INDEX(data + end);
            if (!entry->str[0])
                continue;
            if (strnmatch(entry->str + 2, data + end + 2, length - end - 2))
                tmp = entry->val;
        }
        last += tmp;
    }
    return first * 10 + last;
}
