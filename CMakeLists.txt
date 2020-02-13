cmake_minimum_required(VERSION 3.15)
project(stl_test_sample)

set(CMAKE_CXX_STANDARD 20)

set(MAIN_PROJECT_SRC_LIST main)

add_executable(main ${MAIN_PROJECT_SRC_LIST})

add_subdirectory(stl_test_impl)
target_link_libraries(main stl_test_impl)