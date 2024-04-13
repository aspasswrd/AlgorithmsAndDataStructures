#include <iostream>
#include <stack>
#include <vector>

size_t MaxArea(std::vector<int>& hist) {
  std::stack<size_t> stack;

  size_t max_area = 0;
  size_t current_area;
  size_t top;

  size_t it = 0;
  while (it != hist.size()) {
    if (stack.empty() || (hist[stack.top()] <= hist[it])) {
      stack.push(it);
      ++it;
    } else {
      top = stack.top();
      stack.pop();
      current_area = hist[top] * it;
      if (!stack.empty()) {
        current_area = hist[top] * (it - stack.top() - 1);
      }
      max_area = std::max(current_area, max_area);
    }
  }

  while (!stack.empty()) {
    top = stack.top();
    stack.pop();
    current_area = hist[top] * it;
    if (!stack.empty()) {
      current_area = hist[top] * (it - stack.top() - 1);
    }
    max_area = std::max(current_area, max_area);
  }
  return max_area;
}

int main() {
  int num;
  std::cin >> num;
  std::vector<int> hist(num);
  for (int i = 0; i != num; ++i) {
    std::cin >> hist[i];
  }

  std::cout << MaxArea(hist);
}
