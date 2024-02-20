cmake_minimum_required(VERSION 3.27)
project(moltres C)

# Compiler detection and configuration
find_program(GCC_COMPILER gcc) # Try GCC
if(GCC_COMPILER)
  set(CMAKE_C_COMPILER ${GCC_COMPILER})
else()
  find_program(CLANG_COMPILER clang)
  if(CLANG_COMPILER)
    set(CMAKE_C_COMPILER ${CLANG_COMPILER})
  else()
    find_program(MSVC_COMPILER cl)  # Try Microsoft Visual Studio
    if(MSVC_COMPILER)
      set(CMAKE_C_COMPILER ${MSVC_COMPILER})
    else()
      message(FATAL_ERROR "No suitable C compiler found.")
    endif()
  endif()
endif()


# Global settings
set(CMAKE_C_STANDARD 17)

set(CMAKE_CONFIGURATION_TYPES Debug Release ReleaseWithDebugInfo)

# for clangd lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add Executable
file(GLOB SRC_FILES src/*.c)
add_executable(moltres ${SRC_FILES})

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty
)

# Windows-specific configuration
if(WIN32)
  set(SDL2_PATH "C:/bin/SDL2")
  include_directories(${SDL2_PATH}/include)
  target_link_libraries(moltres PRIVATE
            ${SDL2_PATH}/lib/x64/SDL2main.lib
            ${SDL2_PATH}/lib/x64/SDL2.lib
            ${SDL2_PATH}/lib/x64/SDL2_image.lib
            ${SDL2_PATH}/lib/x64/SDL2_ttf.lib
    )

  # Compiler and linker options for Windows
  if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    target_link_options(moltres PRIVATE "/subsystem:windows")
  elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(moltres PRIVATE -mwindows)
  endif()

  # Define WINDOWS macro
  target_compile_definitions(moltres PRIVATE WINDOWS)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(moltres PRIVATE MOLTRES_DEBUG)
endif()


if(UNIX)
  target_include_directories(moltres PRIVATE /usr/include/SDL2)
  target_link_libraries(moltres PRIVATE -lm -lSDL2 -lSDL2_image -lSDL2_ttf)
endif()

# Debug build configuration
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(moltres PRIVATE -Wall -pedantic)
  target_compile_options(moltres PRIVATE $<$<CONFIG:Debug>:-g -O0>)
  target_compile_options(moltres PRIVATE $<$<CONFIG:Release>:-O3>)
  target_compile_options(moltres PRIVATE $<$<CONFIG:ReleaseWithDebugInfo>:-O3 -g>)
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  target_compile_options(moltres PRIVATE /Wall)
  target_compile_options(moltres PRIVATE $<$<CONFIG:Debug>:/Zi /Od /W4>)
  target_compile_options(moltres PRIVATE $<$<CONFIG:Release>:/O2 /Oi /Ot /GL>)
  target_compile_options(moltres PRIVATE $<$<CONFIG:ReleaseWithDebugInfo>:/O2 /Oi /Ot /GL /Zi>)
endif()
