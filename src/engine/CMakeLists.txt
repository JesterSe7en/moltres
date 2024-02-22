cmake_minimum_required(VERSION 3.27)
project(moltres_engine C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HEADER_FILES
        include/animation.h
        include/entity.h
        include/hashtable.h
        include/main.h
        include/renderwindow.h
        include/utils.h
        include/vector.h
)

set(SOURCE_FILES
        src/animation.c
        src/entity.c
        src/hashtable.c
        src/main.c
        src/renderwindow.c
        src/utils.c
)

add_library(moltres_engine STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(moltres_engine PUBLIC include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/superfasthash/include
)

if (WIN32)
  target_link_libraries(moltres_engine PRIVATE -L${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/SDL2/lib/win -lSDL2 -lSDL2_image -lSDL2_ttf)
else ()
  target_link_libraries(moltres_engine PRIVATE -L${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/SDL2/lib/mingw -lSDL2 -lSDL2_image -lSDL2_ttf)
endif ()

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Debug, Release or RelWithDebInfo")

target_compile_options(moltres_engine PRIVATE -Wall -Wextra -pedantic)
target_compile_options(moltres_engine PRIVATE $<$<CONFIG:Debug>:-g -O0>)
target_compile_options(moltres_engine PRIVATE $<$<CONFIG:Release>:-O3>)
target_compile_options(moltres_engine PRIVATE $<$<CONFIG:ReleaseWithDebugInfo>:-O3 -g>)
