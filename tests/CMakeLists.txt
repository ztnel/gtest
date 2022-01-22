include_directories("${PROJECT_SOURCE_DIR}/include")

message(STATUS "Running test configuration")
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/tests/main.cpp")

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("test_${name}"
    ${sources}
    ${file}
    "${PROJECT_SOURCE_DIR}/tests/main.cpp")
  target_link_libraries("test_${name}" gtest_main)
  add_test(NAME ${name} COMMAND "test_${name}")
endforeach()