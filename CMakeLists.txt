cmake_minimum_required(VERSION 3.10)

project( Hydra
    HOMEPAGE_URL "https://github.com/Reza-namvaran/Hydra"
    VERSION 0.1
    LANGUAGES C
    )

# Set the default generator to "MinGW Makefiles"
if(NOT CMAKE_GENERATOR)
    set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
endif()

# Set compiler options
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd to know include directories

# Configure output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Source files
file(GLOB CORE_SOURCES ${PROJECT_SOURCE_DIR}/src/core/*.c)

add_subdirectory(src/)