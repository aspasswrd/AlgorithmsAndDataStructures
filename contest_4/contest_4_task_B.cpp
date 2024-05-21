#include <iostream>

#define kBillion 1000000000

struct Node {
    int value = 0;
    size_t height = 1;

    Node* left_son = nullptr;
    Node* right_son = nullptr;

    explicit Node(int val) { value = val; }
};

class AVLTree {
 public:
    ~AVLTree() { Delete(root_); }

    Node* GetRoot() { return root_; }

    void Insert(int value) {
        if (root_ == nullptr) {
            root_ = new Node(value);
            return;
        }
        Insert(root_, nullptr, value);
    }

    void Insert(Node* current, Node* current_parent, int value) {
        if (current == nullptr) {
            current = new Node(value);
            if (value < current_parent->value) {
                current_parent->left_son = current;
            } else if (value > current_parent->value) {
                current_parent->right_son = current;
            }
            return;
        }
        if (value < current->value) {
            Insert(current->left_son, current, value);
            current->left_son = BalanceTree(current->left_son);
        } else if (value > current->value) {
            Insert(current->right_son, current, value);
            current->right_son = BalanceTree(current->right_son);
        }
    }

    Node* FindMax(Node* current) {
        if (current == nullptr) {
            return nullptr;
        }
        if (current->right_son == nullptr) {
            return current;
        }
        return FindMax(current->right_son);
    }

    Node* Find(int value) {
        Node* max = FindMax(root_);
        if (max->value < value) {
            return nullptr;
        }
        return Find(root_, value, max);
    }

    Node* Find(Node* current, int value, Node* current_min) {
        if (current == nullptr) {
            return current_min;
        }
        if (current->value == value) {
            return current;
        }
        if (value > current->value) {
            return Find(current->right_son, value, current_min);
        }
        if (value < current->value) {
            if (current->value < current_min->value) {
                current_min = current;
            }
            return Find(current->left_son, value, current_min);
        }
        return current_min;
    }

 private:
    Node* root_ = nullptr;

    static size_t Height(Node* current) {
        return (current != nullptr) ? current->height : 0;
    }

    static int BFactor(Node* current) {
        if (current == nullptr) {
            return 0;
        }
        return int(Height(current->right_son) - Height(current->left_son));
    }

    static void FixHeight(Node* current) {
        size_t h_left = Height(current->left_son);
        size_t h_right = Height(current->right_son);

        current->height = (h_left > h_right ? h_left : h_right) + 1;
    }

    static Node* RotateRight(Node* current) {
        if (current == nullptr) {
            return nullptr;
        }
        Node* new_root = current->left_son;
        if (new_root == nullptr) {
            return nullptr;
        }
        current->left_son = new_root->right_son;
        new_root->right_son = current;
        FixHeight(current);
        FixHeight(new_root);
        return new_root;
    }

    static Node* RotateLeft(Node* current) {
        if (current == nullptr) {
            return nullptr;
        }
        Node* new_root = current->right_son;
        if (new_root == nullptr) {
            return nullptr;
        }
        current->right_son = new_root->left_son;
        new_root->left_son = current;
        FixHeight(current);
        FixHeight(new_root);
        return new_root;
    }

    static Node* BalanceTree(Node* current) {
        FixHeight(current);
        if (BFactor(current) == 2) {
            if (BFactor(current->right_son) < 0) {
                current->right_son = RotateRight(current->right_son);
            }
            return RotateLeft(current);
        }

        if (BFactor(current) == -2) {
            if (BFactor(current->left_son) > 0) {
                current->left_son = RotateLeft(current->left_son);
            }
            return RotateRight(current);
        }
        return current;
    }

    void Delete(Node* current) {
        if (current == nullptr) {
            return;
        }
        Delete(current->left_son);
        Delete(current->right_son);
        delete current;
    }
};

void AnswerQueries(int queries_count) {
    AVLTree tree;
    char sign;
    char previous = '+';
    int previous_answer;
    int value;
    Node* answer;
    for (int i = 0; i != queries_count; ++i) {
        std::cin >> sign;
        switch (sign) {
            case '+':
                std::cin >> value;
                if (previous == '?') {
                    value = (value + previous_answer) % kBillion;
                }
                tree.Insert(value);
                previous = '+';
                break;
            case '?':
                std::cin >> value;
                answer = tree.Find(value);
                if (answer == nullptr) {
                    std::cout << -1 << "\n";
                    previous_answer = -1;
                    break;
                }
                std::cout << answer->value << "\n";
                previous_answer = answer->value;
                previous = '?';
                break;
            default:
                std::cout << "error\n";
        }
    }
}

int main() {
    int queries_count;
    std::cin >> queries_count;

    AnswerQueries(queries_count);
}
