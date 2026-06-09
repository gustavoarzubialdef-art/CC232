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