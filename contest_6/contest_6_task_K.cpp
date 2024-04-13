#include <iostream>
#include <vector>

void ShowMatrix(std::vector<std::vector<int>>& matrix) {
  for (size_t i = 0; i != matrix.size(); ++i) {
    for (size_t j = 0; j != matrix[i].size(); ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int n0;
  int m0;
  std::cin >> n0 >> m0;

  std::vector<int> weights(n0 + 1, 0);
  for (int i = 1; i != n0 + 1; ++i) {
    std::cin >> weights[i];
  }

  std::vector<int> costs(n0 + 1, 0);
  for (int i = 1; i != n0 + 1; ++i) {
    std::cin >> costs[i];
  }

  std::vector<std::vector<int>> dp(n0 + 1, std::vector<int>(m0 + 1, 0));
  for (int i = 1; i != n0 + 1; ++i) {
    for (int j = 1; j != m0 + 1; ++j) {
      if (j >= weights[i]) {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + costs[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  int i0 = n0;
  int j0 = m0;
  std::vector<int> answer;
  while (dp[i0][j0] != 0) {
    if (dp[i0 - 1][j0] == dp[i0][j0]) {
      --i0;
    } else {
      answer.push_back(i0);
      if (i0 < (int)weights.size()) {
        j0 -= weights[i0];
      }
      --i0;
    }
  }

  for (size_t i = 0; i != answer.size(); ++i) {
    std::cout << answer[answer.size() - i - 1] << "\n";
  }
}
