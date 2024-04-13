#include <iostream>
#include <stack>
#include <string>

class QueueWithMinimum {
 public:
    void Clear() {
        while (!in_.empty()) {
            in_.pop();
        }
        while (!out_.empty()) {
            out_.pop();
        }
        std::cout << "ok\n";
    }

    void Enqueue(int num) {
        if (in_.empty()) {
            in_.emplace(num, num);
        } else {
            in_.emplace(num, std::min(num, in_.top().second));
        }
        std::cout << "ok\n";
    }

    [[nodiscard]] size_t Size() const {
        size_t answer = in_.size() + out_.size();
        return answer;
    }

    void Front() {
        if (Size() == 0) {
            std::cout << "error\n";
            return;
        }
        if (out_.empty()) {
            while (!in_.empty()) {
                int num = in_.top().first;
                in_.pop();
                if (out_.empty()) {
                    out_.emplace(num, num);
                } else {
                    out_.emplace(num, std::min(num, out_.top().second));
                }
            }
        }
        std::cout << out_.top().first << "\n";
    }

    void Dequeue() {
        if (Size() == 0) {
            std::cout << "error\n";
            return;
        }
        Front();
        out_.pop();
    }

    void GetMin() {
        if (Size() == 0) {
            std::cout << "error\n";
            return;
        }
        if (in_.empty()) {
            std::cout << out_.top().second << "\n";
            return;
        }
        if (out_.empty()) {
            std::cout << in_.top().second << "\n";
            return;
        }
        std::cout << std::min(out_.top().second, in_.top().second) << "\n";
    }
 private:
    std::stack<std::pair<int, int>> in_;
    std::stack<std::pair<int, int>> out_;
};

void AnswerQueries(int queries_count) {
    QueueWithMinimum queue;
    std::string query;
    int num;
    for (int i = 0; i != queries_count; ++i) {
        std::cin >> query;
        if (query == "enqueue") {
            std::cin >> num;
            queue.Enqueue(num);
        }
        if (query == "dequeue") {
            queue.Dequeue();
        }
        if (query == "front") {
            queue.Front();
        }
        if (query == "size") {
            std::cout << queue.Size() << "\n";
        }
        if (query == "clear") {
            queue.Clear();
        }
        if (query == "min") {
            queue.GetMin();
        }
    }
}

int main() {
    int queries_count;
    std::cin >> queries_count;

    AnswerQueries(queries_count);
}
