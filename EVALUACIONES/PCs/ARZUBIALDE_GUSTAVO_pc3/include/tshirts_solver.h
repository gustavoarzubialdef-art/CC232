#pragma once

#include <iosfwd>
#include <string>
#include <utility>
#include <vector>

namespace pc3 {

struct TShirt {
  long long price{0};
  long long quality{0};
};

std::vector<int> solveFast(const std::vector<TShirt>& shirts,
                           const std::vector<long long>& budgets);

std::vector<int> solveNaive(const std::vector<TShirt>& shirts,
                            const std::vector<long long>& budgets);

bool verifyAgainstNaive(const std::vector<TShirt>& shirts,
                        const std::vector<long long>& budgets);

void printOrderedTrace(const std::vector<TShirt>& shirts,
                       const std::vector<long long>& budgets,
                       std::ostream& out);

}  // namespace pc3