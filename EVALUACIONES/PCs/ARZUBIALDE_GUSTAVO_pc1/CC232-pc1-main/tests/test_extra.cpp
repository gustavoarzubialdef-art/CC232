#include "count_ones_array.h"
#include "count_ones.h"
#include "loop_counter.h"
#include <iostream>
#include <cassert>

int main() {
    LoopCounter c;

    // Test 1: n = 0
    // Algoritmo Optimizado
    {
        auto v = CountOnesArray::computeOptimized(0, c);
        assert(v == std::vector<int>{0});
    }

    // Test 2: valor pequeño
    // Algoritmo Optimizado
    {
        c.reset();
        auto v = CountOnesArray::computeOptimized(5, c);
        std::vector<int> expected = {0,1,1,2,1,2};
        assert(v == expected);
    }

    // Test 3: comparar con la version ingenua
    {
        c.reset();
        LoopCounter c2;
        const int n = 100;
        auto v1 = CountOnesArray::compute(n, countOnes1, c);
        auto v2 = CountOnesArray::computeOptimized(n, c2);

        assert(v1 == v2);
    }

    std::cout << "Prueba extra concluida\n";
    return 0;
}
