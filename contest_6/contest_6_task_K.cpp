#include <iostream>
#include <vector>

struct Solution {
  Solution(int n, int m) : n(n), m(n) {
    weights.resize(n + 1, 0);
    costs.resize(n + 1, 0);
    dp.resize(n + 1, std::vector<int>(m + 1, 0));
  }

  void Read() {
    for (int i = 1; i != n + 1; ++i) {
      std::cin >> weights[i];
    }
    for (int i = 1; i != n + 1; ++i) {
      std::cin >> costs[i];
    }
  }
  
  void Calculate() {
    for (int i = 1; i != n + 1; ++i) {
      for (int j = 1; j != m + 1; ++j) {
        if (j >= weights[i]) {
          dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + costs[i]);
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }
  }
  
  std::vector<int> GetAnswer() {
    std::vector<int> answer;
    int i = n;
    int j = m;
    while (dp[i][j] != 0) {
      if (dp[i - 1][j] == dp[i][j]) {
        --i;
      } else {
        answer.push_back(i);
        if (i < (int)weights.size()) {
          j -= weights[i];
        }
        --i;
      }
    }
    return answer;
  }

  int n;
  int m;
  std::vector<std::vector<int>> dp;
  std::vector<int> weights;
  std::vector<int> costs;
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Solution s = Solution(n, m);
  s.Read();
  s.Calculate();
  auto answer = s.GetAnswer();
  for (size_t i = 0; i != answer.size(); ++i) {
    std::cout << answer[answer.size() - i - 1] << "\n";
  }
}
