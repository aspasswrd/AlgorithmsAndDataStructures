#include <algorithm>
#include <iostream>
#include <vector>

const int cInf = 100'000;
std::vector<bool> used;

struct Graph {
  void AddEdge(int u, int v, int w) {
    edges.push_back({u, v, w});
  }
  std::vector<int> FordBellman(int n0, int s) {
    std::vector<int> answer(n0, cInf);
    std::vector<int> prev(n0, -1);
    std::vector<int> cycle;
    used.resize(n0, false);
    answer[s] = 0;
    used[s] = true;
    for (int k = 0; k != n0; ++k) {
      for (const auto& edge : edges) {
        if (answer[edge[0]] != cInf &&
            answer[edge[0]] + edge[2] < answer[edge[1]]) {
          answer[edge[1]] = answer[edge[0]] + edge[2];
          prev[edge[1]] = edge[0];
          used[edge[1]] = true;
        }
      }
    }
    for (const auto& edge : edges) {
      if (answer[edge[0]] != cInf &&
          answer[edge[0]] + edge[2] < answer[edge[1]]) {
        int v = edge[1];
        for (int i = 1; i != n0; ++i) {
          v = prev[v];
        }
        int start = v;
        cycle.push_back(v);
        while (true) {
          v = prev[v];
          if (v == -1) {
            return {};
          }
          cycle.push_back(v);
          if (v == start) {
            break;
          }
        }
        break;
      }
    }
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
  }

  std::vector<std::vector<int>> edges;
};



signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n0;
  std::cin >> n0;
  Graph g;

  for (int i = 0; i != n0; ++i) {
    for (int j = 0; j != n0; ++j) {
      int w;
      std::cin >> w;
      if (w == cInf) {
        continue;
      }
      g.AddEdge(i, j, w);
    }
  }

  auto cycle = g.FordBellman(n0, 0);
  if (cycle.empty()) {
    for (int i = 1; i != n0; ++i) {
      cycle = g.FordBellman(n0, i);
      if (!cycle.empty()) {
        break;
      }
    }
  }

  if (!cycle.empty()) {
    std::cout << "YES\n";
    std::cout << cycle.size() << "\n";
    for (const auto& x : cycle) {
      std::cout << x + 1 << " ";
    }
  } else {
    std::cout << "NO";
  }
}