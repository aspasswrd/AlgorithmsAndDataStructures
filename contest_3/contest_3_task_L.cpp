#include <iostream>
#include <vector>

struct Node {
    size_t tl = 0;
    size_t tr = 0;
    int value = 0;

    Node* left_son = nullptr;
    Node* right_son = nullptr;

    Node() = default;

    Node(size_t left, size_t right) {
        tl = left;
        tr = right;
    }
};

class PersistentSegmentTree {
private:
    std::vector<Node*> roots_;
    std::vector<Node*> another_nodes_;

    void Build(const std::vector<int>& vec, Node* current) {
        if (current->tl == current->tr) {
            current->value = vec[current->tl - 1];
            return;
        }
        size_t tm = (current->tl + current->tr) / 2;
        auto* left_son = new Node(current->tl, tm);
        auto* right_son = new Node(tm + 1, current->tr);
        another_nodes_.push_back(left_son);
        another_nodes_.push_back(right_son);

        current->left_son = left_son;
        current->right_son = right_son;

        Build(vec, left_son);
        Build(vec, right_son);

        current->value = current->left_son->value + current->right_son->value;
    }

public:
    PersistentSegmentTree(const std::vector<int>& vec) {
        auto* root = new Node(1, vec.size());
        roots_.push_back(root);
        Build(vec, root);
    }

    void Create(size_t parent_version, size_t pos, int new_value) {
        auto* root_node = new Node(roots_[0]->tl, roots_[0]->tr);
        roots_.push_back(root_node);
        auto* root_parent = roots_[parent_version - 1];
        Create(root_node, root_parent, pos, new_value);
    }

    void Create(Node* current, Node* current_parent, size_t pos, int new_value) {
        if (current->tl == pos && current->tr == pos) {
            current->value = new_value;
            return;
        }
        size_t tm = (current->tl + current->tr) / 2;
        if (pos <= tm) {
            current->right_son = current_parent->right_son;
            current->left_son = new Node(current->tl, tm);
            another_nodes_.push_back(current->left_son);
            Create(current->left_son, current_parent->left_son, pos, new_value);
        } else {
            current->left_son = current_parent->left_son;
            current->right_son = new Node(tm + 1, current->tr);
            another_nodes_.push_back(current->right_son);
            Create(current->right_son, current_parent->right_son, pos, new_value);
        }

        current->value = current->left_son->value + current->right_son->value;
    }

    int Get(size_t version, size_t pos) {
        auto* root = roots_[version - 1];
        return Get(root, pos);
    }

    int Get(Node* current, size_t pos) {
        if (current->tl == pos && current->tr == pos) {
            return current->value;
        }
        size_t tm = (current->tl + current->tr) / 2;
        if (pos <= tm) {
            return Get(current->left_son, pos);
        }
        return Get(current->right_son, pos);
    }

    ~PersistentSegmentTree() {
        for (auto* root : roots_) {
            delete root;
        }
        for (auto* node : another_nodes_) {
            delete node;
        }
    }
};

void Solution(int queries_count, std::vector<int>& vec) {
    PersistentSegmentTree tree(vec);
    std::string query;
    for (int i = 0; i != queries_count; ++i) {
        std::cin >> query;
        if (query == "create") {
            size_t parent_version;
            size_t pos;
            int new_value;
            std::cin >> parent_version >> pos >> new_value;
            tree.Create(parent_version, pos, new_value);
        }
        if (query == "get") {
            size_t version;
            size_t pos;
            std::cin >> version >> pos;
            std::cout << tree.Get(version, pos) << "\n";
        }
    }
}

int main() {
    int len;
    std::cin >> len;
    std::vector<int> vec(len);

    for (int i = 0; i != len; ++i) {
        std::cin >> vec[i];
    }

    int queries_count;
    std::cin >> queries_count;

    Solution(queries_count, vec);
}
