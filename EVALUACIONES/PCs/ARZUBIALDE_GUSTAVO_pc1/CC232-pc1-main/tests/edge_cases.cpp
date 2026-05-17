#include "count_ones.h"
#include "count_ones_array.h"
#include <random>
#include <iostream>
#include <cassert>

int main() {
    LoopCounter c1, c2;

    // -------- 1. n = 0 --------
    {
        const int n = 0;
        c1.reset(); c2.reset();

        auto v1 = CountOnesArray::compute(n, countOnes1, c1);
        auto v2 = CountOnesArray::computeOptimized(n, c2);

        assert(v1 == std::vector<int>{0});
        assert(v1 == v2);
    }

    // -------- 2. n = 1 --------
    {
        c1.reset(); c2.reset();

        auto v1 = CountOnesArray::compute(1, countOnes1, c1);
        auto v2 = CountOnesArray::computeOptimized(1, c2);

        assert((v1 == std::vector<int>{0,1}));
        assert(v1 == v2);
    }

    // -------- 3. Potencias de 2 --------
    {
        for (unsigned int k = 0; k < 20; ++k) {
            unsigned int n = 1u << k;

            c1.reset(); c2.reset();

            auto v1 = CountOnesArray::compute(n, countOnes1, c1);
            auto v2 = CountOnesArray::computeOptimized(n, c2);

            assert(v1 == v2);

            // La potencia de dos solo tiene un bit
            assert(v2[n] == 1);
        }
    }

    // -------- 4. Potencias (2^k - 1) todos los bits llenos --------
    {
        for (unsigned int k = 1; k < 20; ++k) {
            unsigned int n = (1u << k) - 1;

            c1.reset(); c2.reset();

            auto v1 = CountOnesArray::compute(n, countOnes1, c1);
            auto v2 = CountOnesArray::computeOptimized(n, c2);

            assert(v1 == v2);

            assert(v2[n] == static_cast<int>(k));
        }
    }

    // -------- 5. Numero grande de operaciones --------
    {
        unsigned int n = 1'000'000;

        c1.reset(); c2.reset();

        auto v1 = CountOnesArray::compute(n, countOnes1, c1);
        auto v2 = CountOnesArray::computeOptimized(n, c2);

        assert(v1 == v2);
    }

    std::cout << "Casos borde finalizados\n";
    return 0;
}
