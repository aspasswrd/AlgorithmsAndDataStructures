#include <iostream>
#include <random>
#include <vector>

const int kMaximumPriority = 1000000000;
const int kMinimumPriority = -1000000000;

struct Node {
  std::pair<std::string, std::string> key;
  int priority;
  Node* left_son = nullptr;
  Node* right_son = nullptr;

  Node(std::pair<std::string, std::string>& q_key, int q_priority) {
    key = q_key;
    priority = q_priority;
  }
};

class Treap {
 public:
  std::pair<Node*, Node*> Split(Node* current,
                                std::pair<std::string, std::string>& key) {
    if (current == nullptr) {
      return std::make_pair(nullptr, nullptr);
    }
    if (key.first > current->key.first) {
      auto splitted = Split(current->right_son, key);
      current->right_son = splitted.first;
      return std::make_pair(current, splitted.second);
    }
    auto splitted = Split(current->left_son, key);
    current->left_son = splitted.second;
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
      return t1;
    }
    t2->left_son = Merge(t1, t2->left_son);
    return t2;
  }

  void Insert(std::pair<std::string, std::string> key) {
    Node* node = new Node(key, GetRandomPriority());
    nodes_.push_back(node);
    auto splitted = Split(root_, node->key);
    splitted.first = Merge(splitted.first, node);
    root_ = Merge(splitted.first, splitted.second);
  }

  std::string Find(std::string& key) {
    Node* node = root_;
    while (node != nullptr) {
      if (node->key.first == key) {
        return node->key.second;
      }
      if (node->key.first < key) {
        node = node->right_son;
      } else {
        node = node->left_son;
      }
    }
    return "error";
  }
  ~Treap() {
    for (auto* node : nodes_) {
      delete node;
    }
  }

 private:
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
  int num;
  std::cin >> num;

  std::string query1;
  std::string query2;

  Treap tree;

  for (int i = 0; i != num; ++i) {
    std::cin >> query1 >> query2;
    tree.Insert(std::make_pair(query1, query2));
    tree.Insert(std::make_pair(query2, query1));
  }

  std::cin >> num;

  for (int i = 0; i != num; ++i) {
    std::cin >> query1;
    std::cout << tree.Find(query1) << "\n";
  }
}
