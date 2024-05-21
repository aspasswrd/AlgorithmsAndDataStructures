#include <iostream>
#include <random>
#include <vector>

const int kMaximumPriority = 1000000000;
const int kMinimumPriority = -1000000000;

struct Node {
  int key;
  int priority;
  size_t size = 1;
  Node* left_son = nullptr;
  Node* right_son = nullptr;

  Node(int q_key, int q_priority) {
    key = q_key;
    priority = q_priority;
  }
};

class Treap {
 public:
  std::pair<Node*, Node*> Split(Node* current, int key) {
    if (current == nullptr) {
      return std::make_pair(nullptr, nullptr);
    }
    if (key > current->key) {
      auto splitted = Split(current->right_son, key);
      current->right_son = splitted.first;
      UpdateSize(current);
      return std::make_pair(current, splitted.second);
    }
    auto splitted = Split(current->left_son, key);
    current->left_son = splitted.second;
    UpdateSize(current);
    return std::make_pair(splitted.first, current);
  }

  Node* Merge(Node* t1, Node* t2) {
    if (t2 == nullptr) {
      return t1;
    }
    if (t1 == nullptr) {
      return t2;
    }
    if (t1->priority > t2->priority) {
      t1->right_son = Merge(t1->right_son, t2);
      UpdateSize(t1);
      return t1;
    }
    t2->left_son = Merge(t1, t2->left_son);
    UpdateSize(t2);
    return t2;
  }

  void Insert(int key) {
    if (Contains(key)) {
      return;
    }
    Node* node = new Node(key, GetRandomPriority());
    nodes_.push_back(node);
    auto splitted = Split(root_, node->key);
    splitted.first = Merge(splitted.first, node);
    root_ = Merge(splitted.first, splitted.second);
  }

  void Erase(int key) { root_ = Erase(root_, key); }

  Node* Erase(Node* current, int key) {
    if (current == nullptr) {
      return current;
    }
    if (current->key == key) {
      current = Merge(current->left_son, current->right_son);
      UpdateSize(current);
      return current;
    }
    if (current->key < key) {
      current->right_son = Erase(current->right_son, key);
      UpdateSize(current);
    } else if (current->key > key) {
      current->left_son = Erase(current->left_son, key);
      UpdateSize(current);
    }
    return current;
  }

  bool Contains(int key) {
    Node* node = root_;
    while (node != nullptr) {
      if (node->key == key) {
        return true;
      }
      if (node->key < key) {
        node = node->right_son;
      } else {
        node = node->left_son;
      }
    }
    return false;
  }

  void Next(int key) { return Next(root_, key); }

  void Next(Node* current, int key) {
    if (current == nullptr) {
      std::cout << "none\n";
      return;
    }
    if (current->key <= key) {
      Next(current->right_son, key);
      return;
    }
    if (current->key > key) {
      if (current->left_son != nullptr && current->left_son->key > key) {
        Next(current->left_son, key);
      } else {
        std::cout << current->key << "\n";
        return;
      }
    }
  }

  void Prev(int key) { return Prev(root_, key); }

  void Prev(Node* current, int key) {
    if (current == nullptr) {
      std::cout << "none\n";
      return;
    }
    if (current->key >= key) {
      Prev(current->left_son, key);
      return;
    }
    if (current->key < key) {
      if (current->right_son != nullptr && current->right_son->key < key) {
        Prev(current->right_son, key);
      } else {
        std::cout << current->key << "\n";
        return;
      }
    }
  }

  void KOrderStatistics(int kth) {
    if ((int)root_->size <= kth || kth < 0) {
      std::cout << "none\n";
    } else {
      return KOrderStatistics(root_, kth);
    }
  }

  void KOrderStatistics(Node* current, int kth) {
    if ((int)Size(current->left_son) == kth) {
      std::cout << current->key << '\n';
      return;
    }
    if ((int)Size(current->left_son) > kth) {
      return KOrderStatistics(current->left_son, kth);
    }
    return KOrderStatistics(current->right_son,
                            kth - (int)Size(current->left_son) - 1);
  }

  ~Treap() {
    for (auto* node : nodes_) {
      delete node;
    }
  }

 private:
  static size_t Size(Node* current) {
    return (current != nullptr) ? current->size : 0;
  }

  static void UpdateSize(Node* current) {
    if (current != nullptr) {
      current->size = 1 + Size(current->left_son) + Size(current->right_son);
    }
  }

  int GetRandomPriority() {
    std::mt19937 gen(rd_());
    std::uniform_int_distribution<> dist(kMinimumPriority, kMaximumPriority);
    return static_cast<int>(dist(gen));
  }

  Node* root_ = nullptr;
  std::vector<Node*> nodes_;
  std::random_device rd_;
};

int main() {
  Treap tree;

  std::string query;
  int val;

  while (std::cin >> query >> val) {
    if (query == "insert") {
      tree.Insert(val);
      continue;
    }
    if (query == "delete") {
      tree.Erase(val);
      continue;
    }
    if (query == "exists") {
      if (tree.Contains(val)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
      continue;
    }
    if (query == "next") {
      tree.Next(val);
      continue;
    }
    if (query == "prev") {
      tree.Prev(val);
      continue;
    }
    if (query == "kth") {
      tree.KOrderStatistics(val);
      continue;
    }
  }
}
