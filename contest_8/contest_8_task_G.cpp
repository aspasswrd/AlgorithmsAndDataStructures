#include <iostream>
#include <vector>

std::vector<std::vector<bool>> Floyd(
    const std::vector<std::vector<bool>>& matrix, int n) {
  std::vector<std::vector<bool>> answer = matrix;
  for (int k = 0; k != n; ++k) {
    for (int i = 0; i != n; ++i) {
      for (int j = 0; j != n; ++j) {
        answer[i][j] = answer[i][j] || (answer[i][k] && answer[k][j]);
      }
    }
  }
  return answer;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<bool>> matrix(n, std::vector<bool>(n, false));

  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      int num;
      std::cin >> num;
      if (num == 1) {
        matrix[i][j] = true;
      }
    }
  }

  auto tr = Floyd(matrix, n);
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      std::cout << tr[i][j] << " ";
    }
    std::cout << "\n";
  }
}