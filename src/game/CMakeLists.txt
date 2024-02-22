cmake_minimum_required(VERSION 3.27)
project(game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HEADER_FILES
    include/main.h
)

set(SOURCE_FILES
    src/main.c
)

add_executable(game ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(game PRIVATE
        include
)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Debug, Release or RelWithDebInfo")

target_compile_options(game PRIVATE -Wall -Wextra -pedantic)
target_compile_options(game PRIVATE $<$<CONFIG:Debug>:-g -O0>)
target_compile_options(game PRIVATE $<$<CONFIG:Release>:-O3>)
target_compile_options(game PRIVATE $<$<CONFIG:ReleaseWithDebugInfo>:-O3 -g>)
