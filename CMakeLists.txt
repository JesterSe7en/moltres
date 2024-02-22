cmake_minimum_required(VERSION 3.27)
project(moltres C)

# Compiler detection and configuration
find_program(GCC_COMPILER gcc) # Try GCC

set(CMAKE_C_STANDARD 11)
set(CMAKE_CONFIGURATION_TYPES Debug Release ReleaseWithDebugInfo)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/engine)
add_subdirectory(src/game)
