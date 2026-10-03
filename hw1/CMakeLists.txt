cmake_minimum_required(VERSION 3.20)
project(hw1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Тесты корректности
add_executable(tests_correctness tests/test_correctness.cpp)
target_include_directories(tests_correctness PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Бенчмарки
add_executable(bench_performance bench/bench_performance.cpp)
target_include_directories(bench_performance PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Оптимизация для Release
if(MSVC)
    target_compile_options(bench_performance PRIVATE $<$<CONFIG:Release>:/O2>)
endif()