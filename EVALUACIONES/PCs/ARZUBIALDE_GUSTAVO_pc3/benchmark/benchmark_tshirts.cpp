#include "tshirts_solver.h"
#include "cc232/PQ_ComplHeap_macro.h"   // ods::pqParent, pqLeftChild, pqRightChild — Semana6

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Ms    = std::chrono::duration<double, std::milli>;

// Genera una instancia aleatoria reproducible
static void makeInstance(int n, int k, std::uint64_t seed,
                         std::vector<pc3::TShirt>& shirts,
                         std::vector<long long>& budgets) {
  std::mt19937_64 rng(seed);
  shirts.resize(n);
  for (auto& s : shirts) {
    s.price   = 1 + (long long)(rng() % 100'000);
    s.quality = 1 + (long long)(rng() % 100'000);
  }
  budgets.resize(k);
  for (auto& b : budgets) {
    b = 1 + (long long)(rng() % 1'000'000);
  }
}

// Muestra indices del heap implicito usando macros de Semana6
static void showHeapIndices(int n) {
  std::cout << "\n--- Indices del heap implicito (ods::pqParent/Left/Right) para n=" << n << " ---\n";
  std::cout << std::setw(6) << "i"
            << std::setw(10) << "parent(i)"
            << std::setw(14) << "leftChild(i)"
            << std::setw(15) << "rightChild(i)" << '\n';
  for (int i = 0; i < std::min(n, 8); ++i) {
    std::cout << std::setw(6) << i
              << std::setw(10) << ods::pqParent((std::size_t)i)
              << std::setw(14) << ods::pqLeftChild((std::size_t)i)
              << std::setw(15) << ods::pqRightChild((std::size_t)i) << '\n';
  }
}

static double measure(const std::vector<pc3::TShirt>& shirts,
                      const std::vector<long long>& budgets,
                      bool fast, int reps = 3) {
  double total = 0.0;
  for (int r = 0; r < reps; ++r) {
    auto t0 = Clock::now();
    if (fast) pc3::solveFast(shirts, budgets);
    else      pc3::solveNaive(shirts, budgets);
    total += Ms(Clock::now() - t0).count();
  }
  return total / reps;
}

int main() {
  std::cout << "=== Benchmark PC3 CC232 — T-Shirts ===\n\n";

  // Muestra uso de macros de heap de Semana6
  showHeapIndices(16);

  struct Case { int n; int k; const char* label; bool runNaive; };
  const Case cases[] = {
    {   50,    200, "pequeno  (n=50,   k=200)",   true  },
    {  200,   1000, "mediano  (n=200,  k=1000)",  true  },
    { 1000,   5000, "grande   (n=1000, k=5000)",  false },
    { 5000,  20000, "xl       (n=5000, k=20000)", false },
    {10000, 100000, "maximo   (n=10k,  k=100k)",  false },
  };

  std::cout << "\n--- Tiempos (promedio de 3 ejecuciones) ---\n";
  std::cout << std::left
            << std::setw(36) << "Caso"
            << std::setw(16) << "solveFast (ms)"
            << std::setw(16) << "solveNaive (ms)"
            << "ratio Fast/Naive\n";
  std::cout << std::string(84, '-') << '\n';

  for (const auto& c : cases) {
    std::vector<pc3::TShirt> shirts;
    std::vector<long long> budgets;
    makeInstance(c.n, c.k, 42, shirts, budgets);

    double tFast  = measure(shirts, budgets, true);
    double tNaive = c.runNaive ? measure(shirts, budgets, false) : -1.0;

    std::cout << std::left  << std::setw(36) << c.label
              << std::right << std::setw(14) << std::fixed << std::setprecision(2) << tFast << "  ";
    if (c.runNaive)
      std::cout << std::setw(14) << tNaive << "  "
                << std::setw(8)  << std::setprecision(3) << tFast / tNaive;
    else
      std::cout << std::setw(14) << "N/A (lento)" << "  " << std::setw(8) << "N/A";
    std::cout << '\n';
  }

  std::cout << "\nNota: solveNaive se omite para casos grandes porque es O(nk).\n";
  std::cout << "La ventaja de solveFast crece con n*k; para n=200,k=1000 ya se\n";
  std::cout << "nota la diferencia entre O(n log k) y O(nk).\n";
  return 0;
}