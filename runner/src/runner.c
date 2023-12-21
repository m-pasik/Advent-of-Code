#include <stdio.h>

#include "runner.h"
#include "utils.h"

const char *const time_units[] = { "ns", "μs", "ms", "s", "min", "h" };
const size_t time_scaling[] = { 1000, 1000, 1000, 60, 60 };
const size_t time_size = sizeof(time_units) / sizeof(char *);

const char *const data_units[] = { "B", "KiB", "MiB", "GiB", "TiB" };
const size_t data_size = sizeof(data_units) / sizeof(char *);

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
    double time = data.time;
    double avg_time = data.avg_time;

    size_t time_unit = 0;
    size_t avg_time_unit = 0;

    while (time > time_scaling[time_unit] && time_unit < time_size - 1)
        time /= time_scaling[time_unit++];

    while (avg_time > time_scaling[avg_time_unit] &&
           avg_time_unit < time_size - 1)
        avg_time /= time_scaling[avg_time_unit++];

    double throughput =
            1000000000 * ((double)data.data_size / (double)data.avg_time);
    size_t data_unit = 0;

    while (throughput > 1024 && data_unit < data_size - 1)
        throughput /= 1024, data_unit++;

    printf("%s:\n"
           "\tResult: %" PRId64 "\n"
           "\tTime: %f %s\n"
           "\tAverage time: %f %s\n"
           "\tThroughput: %f %s/s\n",
           description, data.result, time, time_units[time_unit], avg_time,
           time_units[avg_time_unit], throughput, data_units[data_unit]);
}
