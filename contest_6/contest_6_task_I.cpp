#include <algorithm>
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

size_t Lcis(std::vector<int>& vec1, std::vector<int>& vec2) {
  std::vector<std::vector<int>> dp(vec1.size() + 1,
                                   std::vector<int>(vec2.size() + 1, 0));
  std::vector<size_t> prev(vec2.size() + 1);

  for (size_t i = 1; i != vec1.size() + 1; ++i) {
    size_t index = 0;
    int best = 0;
    for (size_t j = 1; j != vec2.size() + 1; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (vec1[i - 1] == vec2[j - 1] && dp[i - 1][j] < best + 1) {
        dp[i][j] = best + 1;
        prev[j] = index;
      }
      if (vec1[i - 1] > vec2[j - 1] && dp[i - 1][j] > best) {
        best = dp[i - 1][j];
        index = j;
      }
    }
  }
  size_t answer = 0;
  for (size_t j = 1; j != vec2.size() + 1; ++j) {
    answer = (size_t)std::max(dp[vec1.size()][j], (int)answer);
  }
  return answer;
}

int main() {
  int n0;
  int m0;

  std::cin >> n0 >> m0;

  std::vector<int> vec1(n0);
  std::vector<int> vec2(m0);

  for (int i = 0; i != n0; ++i) {
    std::cin >> vec1[i];
  }

  for (int i = 0; i != m0; ++i) {
    std::cin >> vec2[i];
  }

  std::cout << Lcis(vec1, vec2);
}
