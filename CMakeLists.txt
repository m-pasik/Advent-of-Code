cmake_minimum_required(VERSION 3.10)
project(advent-of-code VERSION 0.0.1 DESCRIPTION "Advent of code solutions")
CMAKE_POLICY(SET CMP0072 NEW)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (NOT BUILD_TARGET)
    set(BUILD_TARGET "Runner")
endif()

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_RELEASE "-Wall -O3 -march=native")
set(CMAKE_C_FLAGS_DEBUG "-Wall -O0 -fsanitize=address -ggdb")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

if (BUILD_TARGET STREQUAL "Solution")
    if (NOT BUILD_PATH)
        message(FATAL_ERROR "BUILD_PATH not set")
    endif()
    add_library(solution SHARED ${BUILD_PATH}/solution.c)
elseif (BUILD_TARGET STREQUAL "Runner")
    file(GLOB_RECURSE SOURCES runner/src/*.c)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/runner/include)
    add_executable(run ${SOURCES})
else()
    message(FATAL_ERROR "Unknown target: ${BUILD_TARGET}")
endif()
