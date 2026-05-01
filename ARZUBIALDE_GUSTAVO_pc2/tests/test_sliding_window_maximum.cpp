#include "sliding_window_maximum.h"
#include <cassert>
#include <iostream>
#include <vector>

static bool equals(const std::vector<int>& a, const std::vector<int>& b) {
    return a == b;
}

int main() {
    {
        std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        auto result = sliding_window_maximum(nums, 3);
        assert(equals(result, {3, 3, 5, 5, 6, 7}));
    }
    {
        std::vector<int> nums = {1};
        auto result = sliding_window_maximum(nums, 1);
        assert(equals(result, {1}));
    }
    {
        std::vector<int> nums = {4, 2, 2, 1, 3};
        auto result = sliding_window_maximum(nums, 2);
        assert(equals(result, {4, 2, 2, 3}));
    }
    {
        std::vector<int> nums = {4, 2, 2, 1, 3};
        auto result = sliding_window_minimum(nums, 2);
        assert(equals(result, {2, 2, 1, 1}));
    }
    {
        std::vector<int> nums = {-2, -1, -3, -4, -2};
        auto resultMax = sliding_window_maximum(nums, 3);
        auto resultMin = sliding_window_minimum(nums, 3);
        assert(equals(resultMax, {-1, -1, -2}));
        assert(equals(resultMin, {-3, -4, -4}));
    }
    {
        std::vector<int> nums = {-5,-4,-3,-2,-1};
        auto resultMax = sliding_window_maximum(nums, 2);
        assert(equals(resultMax, {-4, -3, -2, -1}));
    }

    std::cout << "All tests passed.\n";
    return 0;
}
