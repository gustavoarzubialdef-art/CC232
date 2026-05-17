#pragma once

#include "loop_counter.h"
#include <vector>

class CountOnesArray {
public:
  using CountFunc = int (*)(unsigned int, LoopCounter &);

  static std::vector<int> compute(unsigned int n, CountFunc func,
                                  LoopCounter &counter);
  static std::vector<int> computeOptimized(unsigned int n,
                                           LoopCounter &counter);
  static std::vector<int> computeSTL(unsigned int n,
                                           LoopCounter &counter);
  static void print(const std::vector<int> &v);
};
