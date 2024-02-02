cmake_minimum_required(VERSION 3.23)
project(lox)

# Introduce the ccache for build speedup
# https://crascit.com/2016/04/09/using-ccache-with-cmake/
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message(STATUS "CCache Found")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
else()
  message(STATUS "CCache Not Found")
endif()

# Prevent cmake in case of not using build folder
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
message(STATUS "LOC_PATH: ${LOC_PATH}")
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory.")
endif()

set(CMAKE_CXX_STANDARD 20)
message(STATUS "Compiler")
message(STATUS " - ID       \t: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS " - Version  \t: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS " - Path     \t: ${CMAKE_CXX_COMPILER}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
set(gtest_build_tests OFF CACHE BOOL "Enable gtest tests" FORCE)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.0
)
set(benchmark_enable_testing OFF CACHE BOOL "Enable gbench tests" FORCE)

FetchContent_MakeAvailable(googletest googlebenchmark)

# Also requires one of: libbfd (gnu binutils), libdwarf, libdw (elfutils)
# When using a stack trace, you must link ${BACKWARD_ENABLE} to the add_library or add_executable command.
# And then, you must call an add_bacward(${PROJECT_NAME}). 
FetchContent_Declare(backward
        GIT_REPOSITORY https://github.com/bombela/backward-cpp
        GIT_TAG v1.6)
FetchContent_MakeAvailable(backward)

# Set compiler flags
add_compile_options(-W -Wall)

add_subdirectory(scanner)