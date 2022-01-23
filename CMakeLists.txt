cmake_minimum_required(VERSION 3.17)

project(gt LANGUAGES C CXX)

# set compiler options
set(CMAKE_C_STANDARD 99)
# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
# stop cmake from including extension in .gnco file resolution for gcov
set(CMAKE_C_OUTPUT_EXTENSION_REPLACE ON)


# Source definitions
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(APPEND sources "${PROJECT_SOURCE_DIR}/main.c")
include_directories("${PROJECT_SOURCE_DIR}/include")
# create executable
add_executable(ci ${sources})

# Setup coverage with gcov
include(tests/CodeCoverage.cmake)
append_coverage_compiler_flags()
set(COVERAGE_EXCLUDES "${PROJECT_SOURCE_DIR}/tests/*" "${PROJECT_SOURCE_DIR}/main.c" "${CMAKE_BIN_DIR}/googletest-src")
setup_target_for_coverage_gcovr_xml(
    NAME cov
    EXECUTABLE GTEST_COLOR=1 ctest -V
)

# Test definitions
configure_file(CMakeLists.txt.in
    googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)
enable_testing()
add_subdirectory(tests)
