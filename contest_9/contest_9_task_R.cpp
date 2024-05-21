// e-maxx code
#include <iostream>
#include <vector>

const int cInf = 1e9;

struct HungarianAlgorithm {
  HungarianAlgorithm(int n, std::vector<std::vector<int>>& costs)
      : n(n), costs(costs) {
    u.resize(n + 1);
    v.resize(n + 1);
    p.resize(n + 1);
    way.resize(n + 1);
  }

  void Algorithm() {
    for (int i = 1; i <= n; ++i) {
      p[0] = i;
      int j0 = 0;
      std::vector<int> minimum(n + 1, cInf);
      std::vector<bool> used(n + 1, false);
      do {
        used[j0] = true;
        int i0 = p[j0];
        int delta = cInf;
        int j1;
        for (int j = 1; j <= n; ++j) {
          if (!used[j]) {
            int cur = costs[i0 - 1][j - 1] - u[i0] - v[j];
            if (cur < minimum[j]) {
              minimum[j] = cur;
              way[j] = j0;
            }
            if (minimum[j] < delta) {
              delta = minimum[j];
              j1 = j;
            }
          }
        }
        for (int j = 0; j <= n; ++j) {
          if (used[j]) {
            u[p[j]] += delta;
            v[j] -= delta;
          } else {
            minimum[j] -= delta;
          }
        }
        j0 = j1;
      } while (p[j0] != 0);

      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0 != 0);
    }
  }

  void PrintAnswer() {
    Algorithm();
    int min_cost = -v[0];
    std::cout << min_cost << "\n";
    for (int j = 1; j <= n; ++j) {
      std::cout << p[j] << " " << j << "\n";
    }
  }

  int n;
  std::vector<std::vector<int>> costs;
  std::vector<int> u;
  std::vector<int> v;
  std::vector<int> p;
  std::vector<int> way;
};

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> costs(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> costs[i][j];
    }
  }
  HungarianAlgorithm alg = HungarianAlgorithm(n, costs);
  alg.PrintAnswer();
}