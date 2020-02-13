cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

project(stl_test_impl VERSION 0.1)

#set(SOURCES )
set(HEADERS set.hpp functional.hpp)

add_library(stl_test_impl SHARED ${HEADERS})

set_target_properties(stl_test_impl PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(stl_test_impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
