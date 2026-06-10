#include "tshirts_solver.h"

#include <iostream>
#include <vector>

int main() {
  std::vector<pc3::TShirt> shirts = {{7, 5}, {3, 5}, {4, 3}};
  std::vector<long long> budgets = {13, 14, 4, 5};
  pc3::printOrderedTrace(shirts, budgets, std::cout);
  return 0;
}