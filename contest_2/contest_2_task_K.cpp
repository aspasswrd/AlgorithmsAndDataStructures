#include <iostream>
#include <stack>
#include <vector>

struct QueueWithMinimum {
  std::stack<std::pair<int, int>> in;
  std::stack<std::pair<int, int>> out;

  void Clear() {
    while (!in.empty()) {
      in.pop();
    }
    while (!out.empty()) {
      out.pop();
    }
  }

  void Enqueue(int num) {
    if (in.empty()) {
      in.emplace(num, num);
    } else {
      in.emplace(num, std::min(num, in.top().second));
    }
  }

  [[nodiscard]] size_t Size() const {
    size_t answer = in.size() + out.size();
    return answer;
  }

  void Front() {
    if (out.empty()) {
      while (!in.empty()) {
        int num = in.top().first;
        in.pop();
        if (out.empty()) {
          out.emplace(num, num);
        } else {
          out.emplace(num, std::min(num, out.top().second));
        }
      }
    }
  }

  void Dequeue() {
    Front();
    out.pop();
  }

  int GetMin() {
    if (in.empty()) {
      return out.top().second;
    }
    if (out.empty()) {
      return in.top().second;
    }
    return std::min(out.top().second, in.top().second);
  }
};

auto FindMinimum(std::vector<std::vector<int>>& matrix, int num, int len) {
  std::vector<std::vector<int>> temporary(num, std::vector<int>(num - len + 1));
  for (int i = 0; i != num; ++i) {
    QueueWithMinimum queue;
    int it = 0;
    for (int j = 0; j != num; ++j) {
      queue.Enqueue(matrix[i][j]);
      if ((int)queue.Size() == len) {
        temporary[i][it++] = queue.GetMin();
        queue.Dequeue();
      }
    }
  }

  std::vector<std::vector<int>> answer(num - len + 1,
                                       std::vector<int>(num - len + 1));
  for (int j = 0; j != num - len + 1; ++j) {
    QueueWithMinimum queue;
    int it = 0;
    for (int i = 0; i != num; ++i) {
      queue.Enqueue(temporary[i][j]);
      if ((int)queue.Size() == len) {
        answer[it++][j] = queue.GetMin();
        queue.Dequeue();
      }
    }
  }

  return answer;
}

int main() {
  int num;
  int len;
  std::cin >> num >> len;
  std::vector<std::vector<int>> matrix(num, std::vector<int>(num));
  for (int i = 0; i != num; ++i) {
    for (int j = 0; j != num; ++j) {
      std::cin >> matrix[i][j];
    }
  }

  std::vector<std::vector<int>> answer;
  answer = FindMinimum(matrix, num, len);

  for (int i = 0; i != num - len + 1; ++i) {
    for (int j = 0; j != num - len + 1; ++j) {
      std::cout << answer[i][j] << " ";
    }
    std::cout << "\n";
  }
}