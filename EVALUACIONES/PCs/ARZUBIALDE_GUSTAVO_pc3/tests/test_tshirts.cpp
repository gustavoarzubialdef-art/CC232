#include "tshirts_solver.h"

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

namespace {

void expectVector(const std::vector<int>& got, const std::vector<int>& expected) {
  if (got != expected) {
    std::cerr << "Esperado:";
    for (int x : expected) {
      std::cerr << ' ' << x;
    }
    std::cerr << "\nObtenido:";
    for (int x : got) {
      std::cerr << ' ' << x;
    }
    std::cerr << '\n';
    assert(false);
  }
}

void sampleOne() {
  std::vector<pc3::TShirt> shirts = {{7, 5}, {3, 5}, {4, 3}};
  std::vector<long long> budgets = {13, 14};
  expectVector(pc3::solveFast(shirts, budgets), {2, 3});
}

void sampleTwo() {
  std::vector<pc3::TShirt> shirts = {{100, 500}, {50, 499}};
  std::vector<long long> budgets = {50, 200, 150, 100};
  expectVector(pc3::solveFast(shirts, budgets), {1, 2, 2, 1});
}

void minimalCase() {
  std::vector<pc3::TShirt> shirts = {{5, 7}};
  std::vector<long long> budgets = {4, 5};
  expectVector(pc3::solveFast(shirts, budgets), {0, 1});
}

void tieByQualityUsesCheaperFirst() {
  std::vector<pc3::TShirt> shirts = {{10, 8}, {3, 8}, {4, 8}};
  std::vector<long long> budgets = {7, 10};
  expectVector(pc3::solveFast(shirts, budgets), {2, 2});
}

void boundaryWithCrossingCustomers() {
  std::vector<pc3::TShirt> shirts = {{5, 10}, {4, 9}, {1, 8}};
  std::vector<long long> budgets = {4, 5, 10};
  expectVector(pc3::solveFast(shirts, budgets), {1, 1, 3});
}

void explicitNaiveComparison() {
  std::vector<pc3::TShirt> shirts = {{6, 2}, {2, 5}, {3, 5}, {10, 1}};
  std::vector<long long> budgets = {1, 2, 5, 8, 20};
  assert(pc3::verifyAgainstNaive(shirts, budgets));
}

void smallRandomAgainstNaive() {
  std::mt19937 rng(232);
  for (int tc = 0; tc < 200; ++tc) {
    int n = 1 + static_cast<int>(rng() % 8);
    int k = 1 + static_cast<int>(rng() % 8);
    std::vector<pc3::TShirt> shirts(n);
    std::vector<long long> budgets(k);
    for (int i = 0; i < n; ++i) {
      shirts[i].price = 1 + static_cast<int>(rng() % 12);
      shirts[i].quality = 1 + static_cast<int>(rng() % 12);
    }
    for (int i = 0; i < k; ++i) {
      budgets[i] = 1 + static_cast<int>(rng() % 30);
    }
    if (!pc3::verifyAgainstNaive(shirts, budgets)) {
      std::cerr << "Fallo aleatorio en caso " << tc << '\n';
      assert(false);
    }
  }
}

}

int main() {
  sampleOne();
  sampleTwo();
  minimalCase();
  tieByQualityUsesCheaperFirst();
  boundaryWithCrossingCustomers();
  explicitNaiveComparison();
  smallRandomAgainstNaive();
  std::cout << "OK: pruebas PC3 T-Shirts superadas\n";
  return 0;
}