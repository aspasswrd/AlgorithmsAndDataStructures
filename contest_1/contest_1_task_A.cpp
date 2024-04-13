#include <cmath>
#include <iostream>
#include <vector>

int RMQ(std::vector<std::vector<int>>& sparse_table, int left, int right) {
  int key = (int)floor(log2(right - left + 1));
  return (int)std::min(sparse_table[key][left],
                        sparse_table[key][right - (int)pow(2, key) + 1]);
}

int main() {
  int numm;
  std::cin >> numm;
  int k_max = (int)floor(log2(numm)) + 1;
  std::vector<std::vector<int>> speeds(k_max, std::vector<int>(numm));
  for (int i = 0; i != numm; ++i) {
    std::cin >> speeds[0][i];
  }

  for (int k = 1; k != k_max; ++k) {
    for (int i = 0; i != numm - pow(2, k) + 1; ++i) {
      speeds[k][i] =
          std::min(speeds[k - 1][i], speeds[k - 1][i + (int)pow(2, k - 1)]);
    }
  }

  int que;
  std::cin >> que;
  for (int i = 0; i != que; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    left -= 1;
    right -= 1;
    std::cout << std::min(RMQ(speeds, 0, left), RMQ(speeds, right, numm - 1))
              << std::endl;
  }
}
