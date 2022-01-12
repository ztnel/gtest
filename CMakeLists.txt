cmake_minimum_required(VERSION 3.13)

project(unit)


set(CMAKE_C_COMPILER /opt/homebrew/Cellar/gcc/11.2.0_3/bin/gcc-11)
##
### Test definitions ###
##
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
# add cmake modules for code coverage
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules)
include(CodeCoverage)

##
### Source definitions ###
##

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(unit ${sources})

append_coverage_compiler_flags_to_target(${PROJECT_NAME} ${PROJECT_TEST_NAME} coverage)