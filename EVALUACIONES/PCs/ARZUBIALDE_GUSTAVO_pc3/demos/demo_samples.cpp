// Corre los dos ejemplos oficiales del enunciado sin pedir entrada.
#include "tshirts_solver.h"

#include <iostream>
#include <vector>

static void run(const char* label,
                const std::vector<pc3::TShirt>& shirts,
                const std::vector<long long>& budgets) {
  std::cout << "--- " << label << " ---\n";
  std::cout << "Camisetas (precio, calidad):";
  for (const auto& s : shirts) {
    std::cout << "  (" << s.price << ", " << s.quality << ")";
  }
  std::cout << "\nPresupuestos:";
  for (long long b : budgets) {
    std::cout << "  " << b;
  }
  std::cout << "\nCompras por comprador:";
  for (int v : pc3::solveFast(shirts, budgets)) {
    std::cout << "  " << v;
  }
  std::cout << "\n\n";
}

int main() {
  // Ejemplo 1 del enunciado: salida esperada  2 3
  run("Ejemplo 1",
      {{7, 5}, {3, 5}, {4, 3}},
      {13, 14});

  // Ejemplo 2 del enunciado: salida esperada  1 2 2 1
  run("Ejemplo 2",
      {{100, 500}, {50, 499}},
      {50, 200, 150, 100});

  return 0;
}