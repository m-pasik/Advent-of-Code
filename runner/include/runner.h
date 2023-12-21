#ifndef RUNNER_H
#define RUNNER_H

#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

/*
 * Function type for solution functions.
 */
typedef int64_t (*SolutionFunc)(const char *, size_t);

/*
 * Type returned by runner.
 */
typedef struct {
    int64_t result;
    int64_t time;
    int64_t avg_time;
    int64_t data_size;
} Solution;

/*
 * To be passed as argument to the runner.
 */
typedef struct {
    SolutionFunc solver;
    size_t runs;
    const char *data;
    size_t data_length;
} RunnerData;

/*
 * Run solution based on information in `data`.
 *
 * @param   data        Struct containing function, number of runs and data.
 * @return  Struct containing result, and total and average time.
 *          Function might write EINVAL to `errno` if data is invalid.
 */
Solution runner(RunnerData data);

/*
 * Run solution based on information in `data`.
 *
 * @param   description Run description.
 * @param   data        Struct containing runner output.
 */
void print_result(const char *description, Solution data);

#endif
