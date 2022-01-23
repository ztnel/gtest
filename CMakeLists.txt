cmake_minimum_required(VERSION 3.17)

project(gt LANGUAGES C CXX)

# set compiler options
set(CMAKE_C_STANDARD 99)
# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_C_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
# stop cmake from including extension in .gnco file resolution for gcov
set(CMAKE_C_OUTPUT_EXTENSION_REPLACE ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
set(CMAKE_TEST_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
set(CMAKE_COVERAGE_OUT_DIR ${CMAKE_BINARY_DIR}/coverage)


# find_program(GCOV_PATH gcov)
# find_program(GCOVR_PATH gcovr)

# if (NOT GCOV_PATH)
#     message(FATAL_ERROR "lcov not found! Aborting...")
# endif()

##
### Source definitions ###
##
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(APPEND sources "${PROJECT_SOURCE_DIR}/main.c")
include_directories("${PROJECT_SOURCE_DIR}/include")
# create executable
add_executable(ci ${sources})

# Coverage
include(tests/CodeCoverage.cmake)
append_coverage_compiler_flags()
link_libraries(--coverage)
set(
    COVERAGE_EXCLUDES
    "${PROJECT_SOURCE_DIR}/tests/*"
    "${PROJECT_SOURCE_DIR}/main.c"
)
setup_target_for_coverage_gcovr_xml(
    NAME cov
    EXECUTABLE GTEST_COLOR=1 ctest -V
)
# create gcov target and run coverage with make
# add_custom_target(gcov
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_COVERAGE_OUT_DIR} 
#     COMMAND ${CMAKE_MAKE_PROGRAM} ci 
# )
# add_custom_command(TARGET gcov
#     COMMENT "Executing gcov. Artefacts will be compiled to: ${CMAKE_BINARY_DIR}/coverage"	
# 	COMMAND ${GCOV_PATH} -abcfu ${CMAKE_SOURCE_DIR}/src/sf1.c -o ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf1.dir/__/src/
# 	COMMAND ${GCOV_PATH} -abcfu ${CMAKE_SOURCE_DIR}/src/sf2.c -o ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf2.dir/__/src/
#     COMMAND ${GCOVR_PATH} -r ${PROJECT_SOURCE_DIR}
# 	DEPENDS "${CMAKE_TEST_DIRECTORY}"
# 	WORKING_DIRECTORY ${CMAKE_COVERAGE_OUT_DIR}
# )
# add_dependencies(gcov ci)
# add coverage linker flag for clang

# cleanup coverage folder
# set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# create gcov clean target. This cleans build and generated .gcno and .gcda aretefacts
# add_custom_target(scrub
#     COMMAND rm -f ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf1.dir/__/src/*.gcno
#     COMMAND rm -f ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf1.dir/__/src/*.gcda
#     COMMAND rm -f ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf2.dir/__/src/*.gcno
#     COMMAND rm -f ${CMAKE_TEST_DIRECTORY}/CMakeFiles/test_sf2.dir/__/src/*.gcda
#     COMMAND echo "-- Coverage artefacts have been removed from ${CMAKE_BINARY_DIR}/coverage"
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

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

