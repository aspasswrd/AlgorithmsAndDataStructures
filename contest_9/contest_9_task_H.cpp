#include <iostream>
#include <vector>

std::vector<bool> used;
std::vector<int> mt;

struct Pair {
  int index;
  bool is_good;
};

bool Dfs(int v, const std::vector<std::vector<int>>& g) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (int u : g[v]) {
    if (mt[u] == -1 || Dfs(mt[u], g)) {
      mt[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n;
  int m;
  int a;
  int b;

  std::cin >> n >> m >> a >> b;
  std::vector<std::vector<Pair>> matrix(n, std::vector<Pair>(m));
  char c;
  int count_places = 0;
  int left_index = 0;
  int right_index = 0;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != m; ++j) {
      std::cin >> c;
      if ((i + j) % 2 == 0) {
        matrix[i][j].index = left_index++;
      } else {
        matrix[i][j].index = right_index++;
      }
      if (c == '.') {
        matrix[i][j].is_good = false;
      } else {
        ++count_places;
        matrix[i][j].is_good = true;
      }
    }
  }
  if (2 * b <= a) {
    std::cout << count_places * b;
    return 0;
  }
  int l = left_index + 1;
  int r = right_index + 1;
  std::vector<std::vector<int>> g(l);
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != m; ++j) {
      if (matrix[i][j].is_good && (i + j) % 2 == 0) {
        if (j != 0 && matrix[i][j - 1].is_good) {
          g[matrix[i][j].index].push_back(matrix[i][j - 1].index);
        }
        if (j != m - 1 && matrix[i][j + 1].is_good) {
          g[matrix[i][j].index].push_back(matrix[i][j + 1].index);
        }
        if (i != 0 && matrix[i - 1][j].is_good) {
          g[matrix[i][j].index].push_back(matrix[i - 1][j].index);
        }
        if (i != n - 1 && matrix[i + 1][j].is_good) {
          g[matrix[i][j].index].push_back(matrix[i + 1][j].index);
        }
      }
    }
  }
  used.resize(l, false);
  mt.resize(r, -1);
  int count = 0;
  for (int i = 0; i != l; ++i) {
    used.assign(l, false);
    if (Dfs(i, g)) {
      ++count;
    }
  }

  std::cout << count * a + (count_places - 2 * count) * b;
}