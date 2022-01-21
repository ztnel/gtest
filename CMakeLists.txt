cmake_minimum_required(VERSION 2.8...3.13)

project(gt LANGUAGES C CXX)

# set compiler options
set(CMAKE_C_STANDARD 99)
# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
# stop cmake from including extension in .gnco file resolution for gcov
set(CMAKE_C_OUTPUT_EXTENSION_REPLACE ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(CMAKE_TEST_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

##
### Source definitions ###
##
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
include_directories("${PROJECT_SOURCE_DIR}/include")
# create executable
add_executable(ci ${sources})

# create gcov target and run coverage with make
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} ci 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_custom_command(TARGET gcov
    COMMENT "Executing gcov. Artefacts will be compiled to: ${CMAKE_BINARY_DIR}/coverage"	
	COMMAND gcov -abcfu ${CMAKE_SOURCE_DIR}/src/*.c -o ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf1.dir/__/src/ ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf2.dir/__/src/ > CoverageSummary.tmp
	COMMAND gcovr -r ${PROJECT_SOURCE_DIR}
    COMMAND cat CoverageSummary.tmp
	DEPENDS "${CMAKE_TEST_DIRECTORY}"
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage)
add_dependencies(gcov ci)
# add coverage linker flag for clang
link_libraries(--coverage)
# cleanup coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# create gcov clean target. This cleans build and generated .gcno and .gcda aretefacts
add_custom_target(scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${ARTEFACTS}
    COMMAND echo "-- Coverage artefacts have been removed from ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

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
