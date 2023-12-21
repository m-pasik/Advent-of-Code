#include <dlfcn.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "input.h"
#include "runner.h"
#include "utils.h"

int main(int argc, char **argv)
{
    /* Check if cmake is installed */
    int cmake_status = system("cmake --version > /dev/null 2>&1");

    if (cmake_status)
        die("`cmake` not found.");

    long year, day;
    size_t nruns;
    const size_t N = 128;
    char solution_dir[N];
    char input_path[N];
    char source_path[N];
    char library_path[N];

    /*
     * Get puzzle information.
     */

    if (argc > 1)
        year = string_to_long(argv[1]);
    else
        year = read_long(stdin);

    CHECK_ERROR(errno); /* Check for error */

    if (argc > 2)
        day = string_to_long(argv[2]);
    else
        day = read_long(stdin);

    CHECK_ERROR(errno);

    if (argc > 3)
        nruns = string_to_ull(argv[3]);
    else
        nruns = read_ull(stdin);

    CHECK_ERROR(errno);

    /*
     * Test if in range.
     */

    if (year < 2015)
        die("Year must be greater than 2015.");

    if (day < 1 || day > 25)
        die("Day must be in in in range [1, 25].");

    /*
     * Generate file paths.
     */

    size_t index = snprintf(solution_dir, N, "%02ld/", year);

    if (!PATH_EXISTS(solution_dir, S_IFDIR))
        die("No solutions for provided year.");

    index += snprintf(solution_dir + index, N - index, "%02ld/", day);

    if (!PATH_EXISTS(solution_dir, S_IFDIR))
        die("No solutions for provided day.");

    strncpy(input_path, solution_dir, N);
    strncpy(source_path, solution_dir, N);
    strncpy(library_path, solution_dir, N);

    snprintf(input_path + index, N - index, "input.txt");
    snprintf(source_path + index, N - index, "solution.c");
    snprintf(library_path + index, N - index, "libsolution.so");

    /*
     * Recompile library if changes have been made.
     */
    struct stat source_stat, library_stat;

    if (stat(source_path, &source_stat) == -1) {
        perror("Error getting information about source file.");
        return 1;
    }

    if (stat(library_path, &library_stat) == -1) {
        perror("Error getting information about library file.");
        return 1;
    }

    if (source_stat.st_mtime > library_stat.st_mtime) {
        printf("Recompiling solution...\n");
        char command[N + 73];
        snprintf(command, N + 73,
            "cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TARGET=Solution -DBUILD_PATH=%s/ .",
            solution_dir);
        system(command);
        system("cmake --build .");
    }

    /*
     * Read input file.
     */

    FILE *input_file = fopen(input_path, "r");
    if (input_file == NULL)
        die("Failed to open input file.");

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fclose(input_file);
        die("Memory allocation failed.");
    }

    size_t read_size = fread(buffer, 1, file_size, input_file);

    if (read_size != file_size) {
        fclose(input_file);
        free(buffer);
        die("Error reading file.");
    }

    buffer[file_size] = '\0';

    fclose(input_file);

    /*
     * Open solution library.
     */

    void *handle = dlopen(library_path, RTLD_LAZY);
    if (!handle) {
        free(buffer);
        die("Failed to open shared library.");
    }

    SolutionFunc solution_p1 = dlsym(handle, "solution_p1");

    if (!solution_p1) {
        free(buffer);
        dlclose(handle);
        die("Failed loading solution_p1.");
    }

    RunnerData data_p1 = { solution_p1, nruns, buffer, read_size };
    Solution result_p1 = runner(data_p1);

    print_result("Part 1", result_p1);

    SolutionFunc solution_p2 = dlsym(handle, "solution_p2");

    if (!solution_p2) {
        free(buffer);
        dlclose(handle);
        die("Failed loading solution_p1.");
    }

    RunnerData data_p2 = { solution_p2, nruns, buffer, read_size };
    Solution result_p2 = runner(data_p2);

    print_result("Part 2", result_p2);

    free(buffer);
    dlclose(handle);

    return EXIT_SUCCESS;
}