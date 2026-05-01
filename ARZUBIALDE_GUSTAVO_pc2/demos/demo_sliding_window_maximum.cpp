#include "sliding_window_maximum.h"
#include <iostream>
#include <vector>

static void print_vector(const std::vector<int>& values) {
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i + 1 < values.size()) {
            std::cout << " ";
        }
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    std::cout << "Example input:\n";
    std::cout << "nums = [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i];
        if (i + 1 < nums.size()) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << "k = " << k << "\n\n";

    auto maximums = sliding_window_maximum(nums, k);
    auto minimums = sliding_window_minimum(nums, k);

    std::cout << "Sliding window maximums:\n";
    print_vector(maximums);
    std::cout << "Sliding window minimums:\n";
    print_vector(minimums);

    return 0;
}