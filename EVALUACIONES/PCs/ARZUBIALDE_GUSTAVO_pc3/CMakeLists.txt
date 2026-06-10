cmake_minimum_required(VERSION 3.20)
project(PC3_CC232_TShirts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(tshirts_core
    src/tshirts_solver.cpp
)
target_include_directories(tshirts_core PUBLIC include)

# Binario compatible con Codeforces (entrada interactiva con prompts)
add_executable(tshirts src/main.cpp)
target_link_libraries(tshirts PRIVATE tshirts_core)

# Pruebas unitarias
add_executable(test_tshirts tests/test_tshirts.cpp)
target_link_libraries(test_tshirts PRIVATE tshirts_core)
add_test(NAME test_tshirts COMMAND test_tshirts)

# Demo: traza interna del Treap camiseta por camiseta
add_executable(demo_trace demos/demo_trace.cpp)
target_link_libraries(demo_trace PRIVATE tshirts_core)
add_test(NAME demo_trace COMMAND demo_trace)

# Demo: ejemplos oficiales sin entrada interactiva
add_executable(demo_samples demos/demo_samples.cpp)
target_link_libraries(demo_samples PRIVATE tshirts_core)
add_test(NAME demo_samples COMMAND demo_samples)