#include <iostream>
#include <vector>

int BinSearch(std::vector<int>& vec1, std::vector<int>& vec2) {
  int left = 0;
  int right = (int)vec1.size();
  int mid = (right + left - 1) / 2;
  int current_min = std::max(vec1[mid], vec2[mid]);
  int cur_it = mid;

  while (true) {
    if (right - left <= 1) {
      if (std::max(vec1[left], vec2[left]) < current_min) {
        return ++left;
      }
      return ++cur_it;
    }
    mid = (right + left - 1) / 2;
    if (std::max(vec1[mid], vec2[mid]) < current_min) {
      current_min = std::max(vec1[mid], vec2[mid]);
      cur_it = mid;
    }
    if (vec1[mid] == vec2[mid]) {
      return ++mid;
    }
    if (vec1[mid] < vec2[mid]) {
      left = ++mid;
    } else {
      right = mid;
    }
  }
}

int main() {
  int len_a;
  int len_b;
  int len;
  std::cin >> len_a >> len_b >> len;
  std::vector<std::vector<int>> matrix_a(len_a, std::vector<int>(len));
  std::vector<std::vector<int>> matrix_b(len_b, std::vector<int>(len));

  for (int i = 0; i != len_a; ++i) {
    for (int j = 0; j != len; ++j) {
      std::cin >> matrix_a[i][j];
    }
  }

  for (int i = 0; i != len_b; ++i) {
    for (int j = 0; j != len; ++j) {
      std::cin >> matrix_b[i][j];
    }
  }

  int que;
  std::cin >> que;
  for (int i = 0; i != que; ++i) {
    int it1;
    int it2;
    std::cin >> it1 >> it2;
    std::cout << BinSearch(matrix_a[it1 - 1], matrix_b[it2 - 1]) << "\n";
  }
}
