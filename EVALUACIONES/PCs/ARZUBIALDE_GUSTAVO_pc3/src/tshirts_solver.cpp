#include "tshirts_solver.h"

#include "cc232/BinaryHeap.h"   // ods::BinaryHeap  — Semana5
#include "cc232/Treap.h"        // ods::Treap::Node — Semana6

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>

namespace pc3 {
namespace {

// CustomerNode: extiende ods::Treap<int>::Node
struct CustomerNode : public ods::Treap<int>::Node {
  long long money{0};
  int bought{0};
  long long lazyMoney{0};
  int lazyBought{0};

  CustomerNode() = default;
  CustomerNode(int id, long long m, std::uint64_t prio)
      : money(m) {
    key      = id;
    priority = prio;
    parent   = nullptr;
    left     = nullptr;
    right    = nullptr;
  }

  // Acceso tipado a hijos (evita casts repetidos en el codigo)
  CustomerNode* lc() const { return static_cast<CustomerNode*>(left);  }
  CustomerNode* rc() const { return static_cast<CustomerNode*>(right); }
  CustomerNode* par() const { return static_cast<CustomerNode*>(parent); }
};

// CustomerTreap
struct CustomerTreap {
  CustomerNode* root{nullptr};
  std::mt19937_64 rng{232702};
  std::vector<CustomerNode*> owned;
  std::vector<CustomerNode*> byId;
  bool enableInvariantChecks{false};

  ~CustomerTreap() {
    for (CustomerNode* n : owned) delete n;
  }

  // Aplica delta a un subarbol entero en O(1)
  static void addLazy(CustomerNode* n, long long dm, int db) {
    if (!n) return;
    n->money      += dm;
    n->lazyMoney  += dm;
    n->bought     += db;
    n->lazyBought += db;
  }

  // Propaga lazy a los hijos antes de descender
  static void push(CustomerNode* n) {
    if (!n) return;
    if (n->lazyMoney != 0 || n->lazyBought != 0) {
      addLazy(n->lc(), n->lazyMoney, n->lazyBought);
      addLazy(n->rc(), n->lazyMoney, n->lazyBought);
      n->lazyMoney  = 0;
      n->lazyBought = 0;
    }
  }

  // Orden del Treap: (money, id)
  static bool less(const CustomerNode* a, const CustomerNode* b) {
    if (a->money != b->money) return a->money < b->money;
    return a->key < b->key;
  }

  // merge: une dos subarboles ya ordenados.
  // Raiz = nodo con menor priority (invariante heap de ods::Treap).
  static CustomerNode* merge(CustomerNode* L, CustomerNode* R) {
    if (!L) return R;
    if (!R) return L;
    if (L->priority < R->priority) {
      push(L);
      L->right = merge(L->rc(), R);
      if (L->right) L->right->parent = L;
      L->parent = nullptr;
      return L;
    }
    push(R);
    R->left = merge(L, R->lc());
    if (R->left) R->left->parent = R;
    R->parent = nullptr;
    return R;
  }

  // splitLessThan: separa nodos con money < threshold (izquierda)
  // de nodos con money >= threshold (derecha).
  static std::pair<CustomerNode*, CustomerNode*>
  splitLessThan(CustomerNode* n, long long threshold) {
    if (!n) return {nullptr, nullptr};
    push(n);
    if (n->money < threshold) {
      auto [ll, lr] = splitLessThan(n->rc(), threshold);
      n->right = ll;
      if (ll) ll->parent = n;
      n->parent = nullptr;
      if (lr) lr->parent = nullptr;
      return {n, lr};
    }
    auto [ll, lr] = splitLessThan(n->lc(), threshold);
    n->left = lr;
    if (lr) lr->parent = n;
    n->parent = nullptr;
    if (ll) ll->parent = nullptr;
    return {ll, n};
  }

  // insert: inserta un nodo suelto respetando (money,id) y priority.
  static CustomerNode* insert(CustomerNode* r, CustomerNode* n) {
    n->left = n->right = nullptr;
    if (!r) return n;
    push(r);
    if (n->priority < r->priority) {
      auto [ll, lr] = splitByNode(r, n);
      n->left  = ll;  if (ll) ll->parent = n;
      n->right = lr;  if (lr) lr->parent = n;
      n->parent = nullptr;
      return n;
    }
    if (less(n, r)) {
      r->left = insert(r->lc(), n);
      if (r->left) r->left->parent = r;
    } else {
      r->right = insert(r->rc(), n);
      if (r->right) r->right->parent = r;
    }
    return r;
  }

  static std::pair<CustomerNode*, CustomerNode*>
  splitByNode(CustomerNode* r, CustomerNode* pivot) {
    if (!r) return {nullptr, nullptr};
    push(r);
    if (less(r, pivot)) {
      auto [ll, lr] = splitByNode(r->rc(), pivot);
      r->right = ll; if (ll) ll->parent = r;
      r->parent = nullptr;
      if (lr) lr->parent = nullptr;
      return {r, lr};
    }
    auto [ll, lr] = splitByNode(r->lc(), pivot);
    r->left = lr; if (lr) lr->parent = r;
    r->parent = nullptr;
    if (ll) ll->parent = nullptr;
    return {ll, r};
  }

  // Recorre un subarbol desconectado y reinserta nodo a nodo.
  static void collectAndInsert(CustomerNode*& r, CustomerNode* sub) {
    if (!sub) return;
    push(sub);
    CustomerNode* L = sub->lc();
    CustomerNode* R = sub->rc();
    sub->left = sub->right = sub->parent = nullptr;
    r = insert(r, sub);
    collectAndInsert(r, L);
    collectAndInsert(r, R);
  }

  CustomerNode* makeNode(long long money, int id) {
    auto* n = new CustomerNode(id, money, rng());
    owned.push_back(n);
    return n;
  }

  void build(const std::vector<long long>& budgets) {
    byId.assign(budgets.size(), nullptr);
    enableInvariantChecks = (budgets.size() <= 256);
    for (int i = 0; i < (int)budgets.size(); ++i) {
      CustomerNode* n = makeNode(budgets[i], i);
      byId[i] = n;
      root = insert(root, n);
    }
    assertInvariantIfSmall();
  }

  // Operacion central: por cada camiseta de precio c,
  // resta c y suma 1 compra a todos los compradores con money >= c.
  void buyForEligible(long long price) {
    auto [unable, eligible] = splitLessThan(root, price);
    addLazy(eligible, -price, 1);
    auto [crossed, stillOk] = splitLessThan(eligible, price);
    collectAndInsert(unable, crossed);
    root = merge(unable, stillOk);
    assertInvariantIfSmall();
  }

  // Validacion con ods::Treap
  static bool checkOrdered(CustomerNode* n, CustomerNode*& prev) {
    if (!n) return true;
    push(n);
    if (!checkOrdered(n->lc(), prev)) return false;
    if (prev && !less(prev, n))       return false;
    prev = n;
    return checkOrdered(n->rc(), prev);
  }

  // Verifica propiedad BST (orden inorder por (money,id))
  bool checkBST() const {
    CustomerNode* prev = nullptr;
    return checkOrdered(root, prev);
  }

  // Verifica propiedad heap por priority (igual que ods::Treap::isHeapByPriority)
  static bool checkHeap(CustomerNode* n) {
    if (!n) return true;
    if (n->lc() && n->lc()->priority < n->priority) return false;
    if (n->rc() && n->rc()->priority < n->priority) return false;
    return checkHeap(n->lc()) && checkHeap(n->rc());
  }

  // Equivalente a ods::Treap::isTreap(): BST por clave + heap por priority
  bool checkInvariant() const {
    return checkBST() && checkHeap(root);
  }

  void assertInvariantIfSmall() {
    if (enableInvariantChecks) assert(checkInvariant());
  }

  std::vector<int> answers() {
    if (!checkInvariant())
      throw std::logic_error("Treap invariant failed before reading answers");
    std::vector<int> ans(byId.size());
    for (int i = 0; i < (int)byId.size(); ++i)
      ans[i] = byId[i]->bought;
    return ans;
  }

  void dumpInorder(CustomerNode* n, std::ostream& out) const {
    if (!n) return;
    push(n);
    dumpInorder(n->lc(), out);
    out << "(id=" << n->key + 1
        << ", dinero=" << n->money
        << ", compra=" << n->bought << ") ";
    dumpInorder(n->rc(), out);
  }
};

// sortedShirts: usa ods::BinaryHeap (Semana5)
struct ShirtCmp {
  bool operator()(const TShirt& a, const TShirt& b) const {
    // BinaryHeap es min-heap: queremos extraer mayor calidad primero,
    // por eso invertimos: "a < b" si a tiene MENOR prioridad de extraccion.
    if (a.quality != b.quality) return a.quality > b.quality;  // mayor calidad = menor en el heap
    return a.price < b.price;                                   // menor precio = menor en el heap
  }
};

std::vector<TShirt> sortedShirts(const std::vector<TShirt>& shirts) {
  // Construye heap con comparador: extrae en orden (calidad desc, precio asc)
  ods::BinaryHeap<TShirt, ShirtCmp> heap(shirts);
  std::vector<TShirt> ordered;
  ordered.reserve(shirts.size());
  while (!heap.empty()) {
    ordered.push_back(heap.remove());
  }
  return ordered;
}

// Función de debug: imprime inorder y verifica invariante
void printFinalStateAndVerifyInvariant(CustomerTreap& treap, int k) {
  std::cout << "\n=== VERIFICACIÓN DE INVARIANTE ===" << std::endl;
  std::cout << "Estado final del Treap (inorder por dinero): " << std::endl;

  //Inorder tranversal usando dumpInorder que ya existe
  treap.dumpInorder(treap.root, std::cout);
  std::cout << std::endl;

  // Verificación de invariante
  bool bstOk = treap.checkBST();
  bool heapOk = treap.checkHeap(treap.root);

  std::cout << "\nVerificación de propiedad: " << std::endl;
  std::cout << "  Propiedad BST (inorder ordenado): "
            << (bstOk ? "✓ PASS" : "✗ FAIL") << std::endl; 
  std::cout << "  Propiedad Heap (prioridades): "
            << (heapOk ? "✓ PASS" : "✗ FAIL") << std::endl;

  if (bstOk && heapOk) {
    std::cout << "\n✓ INVARIANTE VERIFICADO: Treap es válido" << std::endl;
  } else {
    std::cerr << "\n✗ ERROR: Invariante roto - hay bug en la implementación" << std::endl;
  }
  std::cout << "================================\n" << std::endl;
}

}

// API publica
std::vector<int> solveFast(const std::vector<TShirt>& shirts,
                           const std::vector<long long>& budgets) {
  CustomerTreap treap;
  treap.build(budgets);
  for (const TShirt& s : sortedShirts(shirts))
    treap.buyForEligible(s.price);
  
  // Verificación explícita de invariante (Bloque 6 - modificación grabada)
  std::vector<int> result = treap.answers();
  printFinalStateAndVerifyInvariant(treap, (int)budgets.size());

  return result;
}

std::vector<int> solveNaive(const std::vector<TShirt>& shirts,
                            const std::vector<long long>& budgets) {
  std::vector<TShirt> ordered = sortedShirts(shirts);
  std::vector<int> answer(budgets.size(), 0);
  for (int i = 0; i < (int)budgets.size(); ++i) {
    long long rem = budgets[i];
    for (const TShirt& s : ordered) {
      if (rem >= s.price) { rem -= s.price; ++answer[i]; }
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
  for (const TShirt& s : ordered) {
    out << "Camiseta precio=" << s.price << " calidad=" << s.quality << '\n';
    treap.buyForEligible(s.price);
    out << "Estado despues: ";
    treap.dumpInorder(treap.root, out);
    out << '\n';
  }
}

}  // namespace pc3