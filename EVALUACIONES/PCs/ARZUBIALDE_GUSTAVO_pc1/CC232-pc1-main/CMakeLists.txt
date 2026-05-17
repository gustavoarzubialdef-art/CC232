cmake_minimum_required(VERSION 3.20)

option(BUILD_BENCHMARKS "Build benchmark targets" ON)
option(ENABLE_SANITIZERS "Enable ASan and UBSan" ON)
enable_testing()

add_library(algorithms STATIC
  "src/count_ones.cpp"
  "src/count_ones_array.cpp"
  "src/loop_counter.cpp"
)

add_compile_options(-Wall -Wextra -Wpedantic)

target_include_directories(algorithms PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(demo_countones "demos/demo_countones.cpp")
target_link_libraries(demo_countones PRIVATE algorithms)

add_executable(test_extra "tests/test_extra.cpp")
target_link_libraries(test_extra PRIVATE algorithms)


add_executable(test_internal "tests/test_internal.cpp")
target_link_libraries(test_internal PRIVATE algorithms)


add_executable(edge_cases "tests/edge_cases.cpp")
target_link_libraries(edge_cases PRIVATE algorithms)

add_test(NAME pc1_test_internal COMMAND test_internal)
add_test(NAME pc1_test_extr COMMAND test_extra)
add_test(NAME pc1_edge_cases COMMAND edge_cases)

if (BUILD_BENCHMARKS)
    add_executable(benchmark benchmarks/benchmark.cpp)
    target_link_libraries(benchmark PRIVATE algorithms)
endif()
if (ENABLE_SANITIZERS)
    message(STATUS "Sanitizers enabled")

    add_compile_options(
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -g
    )

    add_link_options(
        -fsanitize=address,undefined
    )
endif()
