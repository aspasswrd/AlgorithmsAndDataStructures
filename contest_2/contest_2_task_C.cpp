#include <deque>
#include <iostream>

void UpdateQueue(std::deque<int>& left, std::deque<int>& right) {
  if (right.size() - left.size() > 0) {
    left.push_back(right.front());
    right.pop_front();
  }
}

void AnswerQueries(int queries_count) {
  std::deque<int> left_queue;
  std::deque<int> right_queue;
  char sign;
  int it;
  for (int i = 0; i != queries_count; ++i) {
    std::cin >> sign;
    switch (sign) {
      case '+':
        std::cin >> it;
        right_queue.push_back(it);
        UpdateQueue(left_queue, right_queue);
        break;
      case '*':
        std::cin >> it;
        right_queue.push_front(it);
        UpdateQueue(left_queue, right_queue);
        break;
      case '-':
        std::cout << left_queue.front() << "\n";
        left_queue.pop_front();
        UpdateQueue(left_queue, right_queue);
        break;
      default:
        std::cout << "Error";
    }
  }
}

int main() {
  int queries_count;
  std::cin >> queries_count;

  AnswerQueries(queries_count);
}
