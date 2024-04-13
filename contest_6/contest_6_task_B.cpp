#include <iostream>
#include <vector>

const int kInf = 2147483647;

void ShowMatrix(std::vector<std::vector<int>>& matrix) {
  for (size_t i = 0; i != matrix.size(); ++i) {
    for (size_t j = 0; j != matrix[i].size(); ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int sum_of_left_dist(std::vector<int>& coords, int j) {
  int sum = 0;
  for (int i = 1; i != j; ++i) {
    sum += coords[i - 1];
  }
  return ((j - 1) * coords[j - 1] - sum);
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<int> coords(n);
  for (auto& x : coords) {
    std::cin >> x;
  }

  // dp[i][j] i - число точек влияния, j - число домов на префиксе

  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

  for (int j = 1; j != n + 1; ++j) {
    dp[1][j] = sum_of_left_dist(coords, j);
  }

  for (int i = 0; i != m + 1; ++i) {
    for (int j = 1; j != n + 1; ++j) {

    }
  }

  ShowMatrix(dp);
}
