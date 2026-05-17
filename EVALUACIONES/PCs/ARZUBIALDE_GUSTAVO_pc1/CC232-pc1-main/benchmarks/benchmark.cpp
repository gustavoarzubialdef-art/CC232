#include "count_ones.h"
#include "count_ones_array.h"
#include "loop_counter.h"
#include <chrono>
#include <iomanip>
#include <iostream>

int main() {
  constexpr int n = 10000000;
  using namespace std::chrono;

  LoopCounter c0, c1, c2;

  auto start0 = high_resolution_clock::now();
  auto v0 = CountOnesArray::computeSTL(n, c0);
  auto end0 = high_resolution_clock::now();

  volatile int sink0 = v0.back();
  (void)sink0;

  auto start1 = high_resolution_clock::now();
  auto v1 = CountOnesArray::compute(n, countOnes1, c1);
  auto end1 = high_resolution_clock::now();

  volatile int sink1 = v1.back();
  (void)sink1;

  auto start2 = high_resolution_clock::now();
  auto v2 = CountOnesArray::computeOptimized(n, c2);
  auto end2 = high_resolution_clock::now();

  volatile int sink2 = v2.back();
  (void)sink2;

  // -------- Results --------
  auto t0 = duration_cast<milliseconds>(end0 - start0).count();
  auto t1 = duration_cast<milliseconds>(end1 - start1).count();
  auto t2 = duration_cast<milliseconds>(end2 - start2).count();

  std::cout << "\n=== Benchmark (n = " << n << ") ===\n\n";

  std::cout << std::left << std::setw(20) << "Metodo" << std::setw(15)
            << "Tiempo (ms)" << std::setw(20) << "Operaciones"
            << "\n";

  std::cout << std::string(55, '-') << "\n";

  std::cout << std::left << std::setw(20) << "STL" << std::setw(15) << t0
            << std::setw(20) << c1.get() << "\n";

  std::cout << std::left << std::setw(20) << "countOnes1" << std::setw(15) << t1
            << std::setw(20) << c1.get() << "\n";

  std::cout << std::left << std::setw(20) << "Optimizado" << std::setw(15) << t2
            << std::setw(20) << c2.get() << "\n";
  return 0;
}
