cmake_minimum_required(VERSION 3.10)
project(Practica2_CC232 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(sliding_window_maximum src/main.cpp src/sliding_window_maximum.cpp)
add_executable(test_sliding_window_maximum tests/test_sliding_window_maximum.cpp src/sliding_window_maximum.cpp)
add_executable(demo_sliding_window_maximum demos/demo_sliding_window_maximum.cpp src/sliding_window_maximum.cpp)
add_executable(benchmark_sliding_window_maximum benchmark/benchmark_sliding_window_maximum.cpp src/sliding_window_maximum.cpp)
