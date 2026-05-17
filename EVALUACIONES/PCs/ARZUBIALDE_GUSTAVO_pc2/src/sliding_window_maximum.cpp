#include "sliding_window_maximum.h"

#include <deque>

static std::vector<int> sliding_window_extreme(const std::vector<int>& nums, int k, bool findMax) {
    std::vector<int> result;
    if (nums.empty() || k <= 0 || k > static_cast<int>(nums.size())) {
        return result;
    }

    std::deque<int> window; // almacena índices
    result.reserve(nums.size() - k + 1);

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        // eliminar índices fuera de la ventana
        while (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }

        int value = nums[i];
        // mantener deque monótona: decreciente para máximos, creciente para mínimos
        while (!window.empty()) {
            int backValue = nums[window.back()];
            if (findMax ? (backValue < value) : (backValue > value)) {
                window.pop_back();
            } else {
                break;
            }
        }
        window.push_back(i);

        if (i >= k - 1) {
            result.push_back(nums[window.front()]);
        }
    }

    return result;
}

std::vector<int> sliding_window_maximum(const std::vector<int>& nums, int k) {
    return sliding_window_extreme(nums, k, true);
}

std::vector<int> sliding_window_minimum(const std::vector<int>& nums, int k) {
    return sliding_window_extreme(nums, k, false);
}