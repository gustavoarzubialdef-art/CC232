#include "sliding_window_maximum.h"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
    const int n = 100000;
    const int k = 500;
    std::vector<int> nums;
    nums.reserve(n);

    std::mt19937 rng(2026);
    std::uniform_int_distribution<int> dist(-10000, 10000);
    for (int i = 0; i < n; ++i) {
        nums.push_back(dist(rng));
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto result = sliding_window_maximum(nums, k);
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Benchmark: n = " << n << ", k = " << k << "\n";
    std::cout << "Result size: " << result.size() << "\n";
    std::cout << "Elapsed time: " << elapsed << " microseconds\n";

    return 0;
}