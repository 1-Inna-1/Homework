cmake_minimum_required(VERSION 3.20)
project(hw2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека с реализацией матрицы
add_library(matrix_lib dense_matrix.cpp)
target_include_directories(matrix_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Тесты корректности
add_executable(tests_correctness tests/test_correctness.cpp)
target_link_libraries(tests_correctness PRIVATE matrix_lib)

# Бенчмарки производительности
add_executable(bench_performance bench/bench_performance.cpp)
target_link_libraries(bench_performance PRIVATE matrix_lib)

# Оптимизация для Release
if(MSVC)
    target_compile_options(bench_performance PRIVATE $<$<CONFIG:Release>:/O2>)
endif()