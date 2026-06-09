#include "tshirts_solver.h"

#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cerr << "Ingresa n (numero de camisetas): ";
  int n = 0;
  std::cin >> n;
  std::vector<pc3::TShirt> shirts(n);
  std::cerr << "Ingresa " << n << " pares (precio calidad):\n";
  for (int i = 0; i < n; ++i) {
    std::cin >> shirts[i].price >> shirts[i].quality;
  }

  std::cerr << "Ingresa k (numero de compradores): ";
  int k = 0;
  std::cin >> k;
  std::vector<long long> budgets(k);
  std::cerr << "Ingresa " << k << " presupuestos:\n";
  for (int i = 0; i < k; ++i) {
    std::cin >> budgets[i];
  }

  std::vector<int> answer = pc3::solveFast(shirts, budgets);
  std::cout << "Compras por comprador:\n";
  for (int i = 0; i < k; ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << answer[i];
  }
  std::cout << '\n';
  return 0;
}