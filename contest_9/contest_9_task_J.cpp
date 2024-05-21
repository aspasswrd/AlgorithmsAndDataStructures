#include <iostream>
#include <vector>

std::vector<bool> used;
std::vector<int> mt;

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

  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n);
  int u;
  int v;
  for (int i = 0; i != m; ++i) {
    std::cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
  }

  std::vector<std::vector<int>> h(2 * n);
  for (int i = 0; i != n; ++i) {
    for (auto& j : g[i]) {
      h[i].push_back(n + j);
    }
  }

  used.resize(n, false);
  mt.resize(2 * n, -1);

  int ans = n;
  for (int i = 0; i != n; ++i) {
    used.resize(n, false);
    if (Dfs(i, h)) {
      ans--;
    }
  }

  std::cout << ans;
}