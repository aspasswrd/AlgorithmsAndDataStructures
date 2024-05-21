#include <iostream>
#include <vector>

const int cInf = 1e9;
const int cMagic = 30'000;

void FordBellman(const std::vector<std::vector<int>>& edges, std::size_t n0) {
  std::vector<int> answer(n0, cInf);
  answer[0] = 0;
  for (size_t k = 1; k != n0; ++k) {
    for (const auto& edge : edges) {
      if (answer[edge[0]] != cInf &&
          answer[edge[0]] + edge[2] < answer[edge[1]]) {
        answer[edge[1]] = answer[edge[0]] + edge[2];
      }
    }
  }
  for (size_t i = 0; i != n0; ++i) {
    if (answer[i] < cInf) {
      std::cout << answer[i] << " ";
    } else {
      std::cout << cMagic << " ";
    }
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n0;
  size_t m0;
  std::cin >> n0 >> m0;

  std::vector<std::vector<int>> edges(m0, std::vector<int>(3));
  for (size_t i = 0; i != m0; ++i) {
    int u;
    int v;
    int w;
    std::cin >> u >> v >> w;
    u -= 1;
    v -= 1;

    edges[i][0] = u;
    edges[i][1] = v;
    edges[i][2] = w;
  }

  FordBellman(edges, n0);
}
