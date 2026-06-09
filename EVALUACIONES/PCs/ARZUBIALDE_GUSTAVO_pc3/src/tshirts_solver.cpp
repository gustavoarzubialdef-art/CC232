#include "tshirts_solver.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

namespace pc3 {
namespace {

struct CustomerNode {
  long long money{0};
  int id{0};
  int bought{0};
  int lazyBought{0};
  long long lazyMoney{0};
  std::uint64_t priority{0};
  CustomerNode* left{nullptr};
  CustomerNode* right{nullptr};
};

struct CustomerTreap {
  CustomerNode* root{nullptr};
  std::mt19937_64 rng{232702};
  std::vector<CustomerNode*> owned;
  std::vector<CustomerNode*> byId;
  bool enableInvariantChecks{false};

  ~CustomerTreap() {
    for (CustomerNode* node : owned) {
      delete node;
    }
  }

  static void addLazy(CustomerNode* node, long long deltaMoney, int deltaBought) {
    if (node == nullptr) {
      return;
    }
    node->money += deltaMoney;
    node->lazyMoney += deltaMoney;
    node->bought += deltaBought;
    node->lazyBought += deltaBought;
  }

  static bool lessNode(const CustomerNode* a, const CustomerNode* b) {
    if (a->money != b->money) {
      return a->money < b->money;
    }
    return a->id < b->id;
  }

  static void push(CustomerNode* node) {
    if (node == nullptr) {
      return;
    }
    if (node->lazyMoney != 0 || node->lazyBought != 0) {
      addLazy(node->left, node->lazyMoney, node->lazyBought);
      addLazy(node->right, node->lazyMoney, node->lazyBought);
      node->lazyMoney = 0;
      node->lazyBought = 0;
    }
  }

  static CustomerNode* merge(CustomerNode* left, CustomerNode* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->priority < right->priority) {
      push(left);
      left->right = merge(left->right, right);
      return left;
    }
    push(right);
    right->left = merge(left, right->left);
    return right;
  }

  static std::pair<CustomerNode*, CustomerNode*> splitLessThan(CustomerNode* node,
                                                              long long money) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    push(node);
    if (node->money < money) {
      auto parts = splitLessThan(node->right, money);
      node->right = parts.first;
      return {node, parts.second};
    }
    auto parts = splitLessThan(node->left, money);
    node->left = parts.second;
    return {parts.first, node};
  }

  static CustomerNode* insert(CustomerNode* root, CustomerNode* node) {
    node->left = nullptr;
    node->right = nullptr;
    if (root == nullptr) {
      return node;
    }
    push(root);
    if (node->priority < root->priority) {
      auto parts = splitByNode(root, node);
      node->left = parts.first;
      node->right = parts.second;
      return node;
    }
    if (lessNode(node, root)) {
      root->left = insert(root->left, node);
    } else {
      root->right = insert(root->right, node);
    }
    return root;
  }

  static std::pair<CustomerNode*, CustomerNode*> splitByNode(CustomerNode* root,
                                                            CustomerNode* pivot) {
    if (root == nullptr) {
      return {nullptr, nullptr};
    }
    push(root);
    if (lessNode(root, pivot)) {
      auto parts = splitByNode(root->right, pivot);
      root->right = parts.first;
      return {root, parts.second};
    }
    auto parts = splitByNode(root->left, pivot);
    root->left = parts.second;
    return {parts.first, root};
  }

  static void collectAndInsert(CustomerNode*& root, CustomerNode* subtree) {
    if (subtree == nullptr) {
      return;
    }
    push(subtree);
    CustomerNode* left = subtree->left;
    CustomerNode* right = subtree->right;
    subtree->left = nullptr;
    subtree->right = nullptr;
    root = insert(root, subtree);
    collectAndInsert(root, left);
    collectAndInsert(root, right);
  }

  CustomerNode* makeNode(long long money, int id) {
    auto* node = new CustomerNode;
    node->money = money;
    node->id = id;
    node->priority = rng();
    owned.push_back(node);
    return node;
  }

  void build(const std::vector<long long>& budgets) {
    byId.assign(budgets.size(), nullptr);
    enableInvariantChecks = budgets.size() <= 256;
    for (int i = 0; i < static_cast<int>(budgets.size()); ++i) {
      CustomerNode* node = makeNode(budgets[i], i);
      byId[i] = node;
      root = insert(root, node);
    }
    assertInvariantIfSmall();
  }

  void buyForEligible(long long price) {
    auto first = splitLessThan(root, price);
    CustomerNode* unable = first.first;
    CustomerNode* eligible = first.second;
    addLazy(eligible, -price, 1);

    auto second = splitLessThan(eligible, price);
    CustomerNode* crossedBelowPrice = second.first;
    CustomerNode* stillAtLeastPrice = second.second;

    collectAndInsert(unable, crossedBelowPrice);
    root = merge(unable, stillAtLeastPrice);
    assertInvariantIfSmall();
  }

  static bool checkOrdered(CustomerNode* node, CustomerNode*& previous) {
    if (node == nullptr) {
      return true;
    }
    push(node);
    if (!checkOrdered(node->left, previous)) {
      return false;
    }
    if (previous != nullptr && lessNode(node, previous)) {
      return false;
    }
    previous = node;
    return checkOrdered(node->right, previous);
  }

  bool checkInvariant() {
    CustomerNode* previous = nullptr;
    return checkOrdered(root, previous);
  }

  void assertInvariantIfSmall() {
    if (enableInvariantChecks) {
      assert(checkInvariant());
    }
  }

  std::vector<int> answers() {
    if (!checkInvariant()) {
      throw std::logic_error("Treap invariant failed before reading answers");
    }
    std::vector<int> ans(byId.size());
    for (int i = 0; i < static_cast<int>(byId.size()); ++i) {
      ans[i] = byId[i]->bought;
    }
    return ans;
  }

  void dumpInorder(CustomerNode* node, std::ostream& out) {
    if (node == nullptr) {
      return;
    }
    push(node);
    dumpInorder(node->left, out);
    out << "(id=" << node->id + 1 << ", dinero=" << node->money
        << ", compra=" << node->bought << ") ";
    dumpInorder(node->right, out);
  }
};

std::vector<TShirt> sortedShirts(const std::vector<TShirt>& shirts) {
  std::vector<TShirt> ordered = shirts;
  std::sort(ordered.begin(), ordered.end(), [](const TShirt& a, const TShirt& b) {
    if (a.quality != b.quality) {
      return a.quality > b.quality;
    }
    return a.price < b.price;
  });
  return ordered;
}

}  // namespace

std::vector<int> solveFast(const std::vector<TShirt>& shirts,
                           const std::vector<long long>& budgets) {
  CustomerTreap treap;
  treap.build(budgets);
  for (const TShirt& shirt : sortedShirts(shirts)) {
    treap.buyForEligible(shirt.price);
  }
  return treap.answers();
}

std::vector<int> solveNaive(const std::vector<TShirt>& shirts,
                            const std::vector<long long>& budgets) {
  std::vector<TShirt> ordered = sortedShirts(shirts);
  std::vector<int> answer(budgets.size(), 0);
  for (int i = 0; i < static_cast<int>(budgets.size()); ++i) {
    long long remaining = budgets[i];
    for (const TShirt& shirt : ordered) {
      if (remaining >= shirt.price) {
        remaining -= shirt.price;
        ++answer[i];
      }
    }
  }
  return answer;
}

bool verifyAgainstNaive(const std::vector<TShirt>& shirts,
                        const std::vector<long long>& budgets) {
  return solveFast(shirts, budgets) == solveNaive(shirts, budgets);
}

void printOrderedTrace(const std::vector<TShirt>& shirts,
                       const std::vector<long long>& budgets,
                       std::ostream& out) {
  CustomerTreap treap;
  treap.build(budgets);
  std::vector<TShirt> ordered = sortedShirts(shirts);
  out << "Estado inicial: ";
  treap.dumpInorder(treap.root, out);
  out << '\n';
  for (const TShirt& shirt : ordered) {
    out << "Camiseta precio=" << shirt.price << " calidad=" << shirt.quality << '\n';
    treap.buyForEligible(shirt.price);
    out << "Estado despues: ";
    treap.dumpInorder(treap.root, out);
    out << '\n';
  }
}

}  // namespace pc3