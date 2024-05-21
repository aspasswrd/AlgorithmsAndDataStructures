#include <iostream>
#include <vector>

struct Node {
    size_t tl = 0;
    size_t tr = 0;
    int left_value = 0;
    int right_value = 0;

    Node* left_son = nullptr;
    Node* right_son = nullptr;

    Node* parent = nullptr;

    Node() = default;

    Node(Node* node, size_t left, size_t right) {
        parent = node;
        tl = left;
        tr = right;
    }
};

class SegmentTree {
private:
    Node* root_ = nullptr;

    void Build(std::vector<int>& vec, Node* current) {
        if (current->tl == current->tr) {
            if (current->tl % 2 == 0) {
                current->left_value = vec[current->tl - 1];
            } else {
                current->right_value = vec[current->tr - 1];
            }
            return;
        }
        size_t tm = (current->tl + current->tr) / 2;
        auto* left_son = new Node(current, current->tl, tm);
        auto* right_son = new Node(current, tm + 1, current->tr);

        current->left_son = left_son;
        current->right_son = right_son;

        Build(vec, left_son);
        Build(vec, right_son);

        current->left_value = left_son->left_value + right_son->left_value;
        current->right_value = left_son->right_value + right_son->right_value;
    }

public:
    Node* GetRoot() { return root_; }

    SegmentTree(std::vector<int>& vec) {
        root_ = new Node(nullptr, 1, vec.size());
        Build(vec, root_);
    }

    int RSQ(size_t left, size_t right) {
        if (root_ == nullptr) {
            return 0;
        }
        return RSQ(root_, left, right);
    }

    int RSQ(Node* current, size_t left, size_t right) {
        if (current->tl >= left && current->tr <= right) {
            if (left % 2 == 0) {
                return current->left_value - current->right_value;
            }
            return current->right_value - current->left_value;
        }
        if (left > current->tr || right < current->tl) {
            return 0;
        }
        return RSQ(current->left_son, left, right) +
               RSQ(current->right_son, left, right);
    }

    void Update(size_t pos, int new_val) {
        if (root_ == nullptr) {
            return;
        }
        Update(root_, pos, new_val);
    }

    void Update(Node* current, size_t pos, int new_val) {
        if (current->tl == current->tr) {
            if (current->tl % 2 == 0) {
                current->left_value = new_val;
            } else {
                current->right_value = new_val;
            }
            return;
        }
        size_t tm = (current->tl + current->tr) / 2;
        if (pos <= tm) {
            Update(current->left_son, pos, new_val);
        } else {
            Update(current->right_son, pos, new_val);
        }
        current->left_value =
                current->left_son->left_value + current->right_son->left_value;
        current->right_value =
                current->left_son->right_value + current->right_son->right_value;
    }

    void Delete(Node* current) {
        if (current == nullptr) {
            return;
        }
        Delete(current->left_son);
        Delete(current->right_son);
        delete current;
    }
    ~SegmentTree() { Delete(root_); }
};

void Solution(int queries_count, std::vector<int>& vec) {
    SegmentTree tree(vec);
    size_t x1;
    size_t x2;
    size_t x3;
    for (int i = 0; i != queries_count; ++i) {
        std::cin >> x1 >> x2 >> x3;
        if (x1 == 0) {
            tree.Update(x2, static_cast<int>(x3));
        }
        if (x1 == 1) {
            std::cout << tree.RSQ(x2, x3) << "\n";
        }
    }
}

int main() {
    int num;
    std::cin >> num;
    std::vector<int> vec(num);
    for (size_t i = 0; i != vec.size(); ++i) {
        std::cin >> vec[i];
    }

    int queries_count;
    std::cin >> queries_count;
    Solution(queries_count, vec);
}
