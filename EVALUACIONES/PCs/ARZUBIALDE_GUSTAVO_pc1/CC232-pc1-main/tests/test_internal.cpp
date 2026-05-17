#include <cassert>
#include <random>
#include <iostream>
#include "count_ones.h"
#include "count_ones_array.h"

int main() {
    LoopCounter c1, c2;

    // Test 1:
    {
        c1.reset(); c2.reset();

        unsigned int n = 10000;

        auto v1 = CountOnesArray::compute(n, countOnes1, c1);
        auto v2 = CountOnesArray::computeOptimized(n, c2);

        assert(v1 == v2);
    }

    // Test 2: Comparacion aleatoria
    {
        std::mt19937 rng(123);
        std::uniform_int_distribution<unsigned int> dist(0, 100000);

        for (int t = 0; t < 100; ++t) {
            unsigned int n = dist(rng);

            c1.reset(); c2.reset();

            auto v1 = CountOnesArray::compute(n, countOnes1, c1);
            auto v2 = CountOnesArray::computeOptimized(n, c2);

            assert(v1 == v2);
        }
    }

    // Test 3: Un valor grande
    {
        unsigned int n = 10000000;

        c1.reset(); c2.reset();

        CountOnesArray::compute(n, countOnes1, c1);
        CountOnesArray::computeOptimized(n, c2);

        assert(c2.get() < c1.get());
    }

    std::cout << "Prueba privada terminada\n";
    return 0;
}
