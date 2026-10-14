cmake_minimum_required(VERSION 3.20)
project(hw2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tests_correctness tests/test_correctness.cpp matrix.cpp)
target_include_directories(tests_correctness PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(bench_performance bench/bench_performance.cpp matrix.cpp)
target_include_directories(bench_performance PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_compile_options(bench_performance PRIVATE $<$<CONFIG:Release>:/O2>)
endif()