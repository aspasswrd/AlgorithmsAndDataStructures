#include <algorithm>
#include <iostream>
#include <set>
#include <vector>


struct Graph {
  Graph(int n, int m) : n(n), m(m) {
    used.resize(n + m, false);
    g.resize(n + m);
  }

  void AddEdge(int v ,int to) {
    g[v].insert(to);
  }

  void Dfs(int v, const std::vector<std::set<int>>& g) {
    used[v] = true;
    for (int u : g[v]) {
      if (!used[u]) {
        Dfs(u, g);
      }
    }
  }

  void Solution() {
    std::vector<bool> matching(m, false);
    int num;
    for (int i = 0; i != m; ++i) {
      std::cin >> num;
      if (num == 0) {
        continue;
      }
      matching[i] = true;
      g[m + num - 1].insert(i);
      g[i].erase(m + num - 1);
    }

    for (int i = 0; i != m; ++i) {
      if (!matching[i] && !used[i]) {
        Dfs(i, g);
      }
    }
    std::vector<int> left;
    std::vector<int> right;
    for (int i = 0; i != (n + m); ++i) {
      if (!used[i] && i < m) {
        left.push_back(i + 1);
      }
      if (used[i] && i >= m) {
        right.push_back(i - m + 1);
      }
    }
    std::cout << left.size() + right.size() << "\n";
    std::cout << left.size() << " ";
    for (auto& x : left) {
      std::cout << x << " ";
    }
    std::cout << "\n";
    std::cout << right.size() << " ";
    for (auto& x : right) {
      std::cout << x << " ";
    }
  }

  int n;
  int m;
  std::vector<bool> used;
  std::vector<std::set<int>> g;
};

int main() {
  int m;
  int n;
  std::cin >> m >> n;
  Graph g = Graph(n, m);

  int c;
  int num;
  for (int i = 0; i != m; ++i) {
    std::cin >> c;
    for (int j = 0; j != c; ++j) {
      std::cin >> num;
      g.AddEdge(i, m + num - 1);
    }
  }
  g.Solution();
}