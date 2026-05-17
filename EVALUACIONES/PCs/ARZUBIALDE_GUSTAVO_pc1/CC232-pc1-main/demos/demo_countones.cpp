#include <bitset>
#include <iostream>

#include "count_ones.h"
#include "count_ones_array.h"
#include "loop_counter.h"

int main() {
  const int n = 10;
  std::cout << "n = " << n << "\n";
  LoopCounter c1, c2;
  auto v1 = CountOnesArray::compute(10, countOnes1,c1);
  std::cout << "No optimizado:\n\n";
  std::cout << "countOnes1(x) = ";
  CountOnesArray::print(v1);
  std::cout << "\n";
  std::cout << "countOnes1 observable: " << c1.get() << "\n";

  std::cout << "Optimizado:\n\n";

  auto v2 = CountOnesArray::computeOptimized(10, c2);
  std::cout << "countOnesOptimized(x) = ";
  CountOnesArray::print(v2);
  std::cout << "countOnesOptimized observable: " << c2.get() << "\n";
  return 0;
}
