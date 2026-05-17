#include "count_ones_array.h"
#include "loop_counter.h"
#include <iostream>
#include <vector>

std::vector<int> CountOnesArray::compute(unsigned int n, CountFunc func,
                                         LoopCounter &counter) {
  std::vector<int> result;
  result.reserve(n + 1);

  for (unsigned int i = 0; i <= n; ++i) {
    counter.increment(); // count outer loop
    result.push_back(func(i, counter));
  }

  return result;
}

std::vector<int> CountOnesArray::computeOptimized(unsigned int n,
                                                  LoopCounter &counter) {
  std::vector<int> result(n+1,0);

  for (unsigned int i = 1; i <= n; ++i) {
    counter.increment();

    result[i] = result[i >> 1] + (i & 1);
  }

  return result;
}

std::vector<int> CountOnesArray::computeSTL(unsigned int n,
                                            LoopCounter &counter) {
  std::vector<int> result;
  result.reserve(n + 1);

  for (unsigned int i = 0; i <= n; ++i) {
    counter.increment();

    int stl_res = __builtin_popcount(i);
    result.push_back(stl_res);
  }

  return result;
}

void CountOnesArray::print(const std::vector<int> &v) {
  std::cout << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i != v.size() - 1) {
      std::cout << v[i] << ", ";
    } else {
      std::cout << v[i];
    }
  }
  std::cout << "]\n";
}
