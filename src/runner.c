#include <stdio.h>

#include "runner.h"
#include "utils.h"

const char *units[] = {
    "B",
    "KiB",
    "MiB",
    "GiB",
    "TiB"
};

size_t units_size = sizeof(units) / sizeof(char *);

Solution runner(RunnerData data)
{
    Solution solution = { 0, 0, 0, 0 };
    if (data.solver == NULL || data.data == NULL || data.runs < 1) {
        errno = EINVAL;
        return solution;
    }

    size_t start = gettime();
    for (size_t i = 1; i < data.runs; i++)
        data.solver(data.data, data.data_length);
    solution.result = data.solver(data.data, data.data_length);
    size_t end = gettime();

    solution.time = end - start;
    solution.avg_time = solution.time / data.runs;
    solution.data_size = data.data_length;

    return solution;
}

void print_result(const char *description, Solution data)
{
    double throughput = 1000000000 * ((double)data.data_size / (double)data.avg_time);
    size_t unit = 0;

    while (throughput > 1024 && unit < units_size - 1)
        throughput /= 1024, unit++;

    printf("%s:\n"
           "\tResult: %" PRId64 "\n"
           "\tTime: %" PRId64 " ns\n"
           "\tAverage time: %" PRId64 " ns\n"
           "\tThroughput: %f %s/s\n",
        description, data.result, data.time, data.avg_time, throughput, units[unit]);
}
