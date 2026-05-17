set -x
echo "COMPILANDO..."
echo "BUILD DE DEPURACION"

g++ -std=c++17 -O0 -g -Wall -Wextra -Wpedantic \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/test_depuracion


echo "BUILD DE DEPURACION OPTIMIZADO"

g++ -std=c++17 -Og -g -Wall -Wextra -Wpedantic \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/test_optimizado


echo "BUILD RELEASE"

g++ -std=c++17 -O2 -g -Wall -Wextra -Wpedantic \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/test_release


echo "BUILD COMPACTO"

g++ -std=c++17 -Os -g -Wall -Wextra -Wpedantic \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/test_compacto


echo "BUILD -O1"

g++ -std=c++17 -O1 -g -Wall -Wextra -Wpedantic \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/test_O1


echo "BUILD -O3"

g++ -std=c++17 -O3 -g -Wall -Wextra -Wpedantic \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/test_O3

echo "COBERTURA"

g++ -std=c++17 --coverage -O0 \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/coverage

echo "PROFILING"

g++ -std=c++17 -O2 -pg \
    src/count_ones.cpp \
    src/count_ones_array.cpp \
    src/loop_counter.cpp \
    tests/test_internal.cpp \
    -Iinclude \
    -o ./build_with_flags/profiling
echo "COMPILACION TERMINADA"
