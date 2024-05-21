#include <cmath>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> up;
std::vector<int> tin;
std::vector<int> tout;

std::vector<int> h;

int timer = 0;
int n = 0;
const int cLogn = 20;

std::vector<std::vector<int>> g;

void Dfs(int v, int p = 0) {
  tin[v] = ++timer;
  up[v][0] = p;
  if (v > 0) {
    h[v] = h[p] + 1;
  }
  for (int i = 1; i < cLogn; ++i) {
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (to != p) {
      Dfs(to, v);
    }
  }
  tout[v] = ++timer;
}

bool A(int u, int v) { return tin[u] <= tin[v] && tin[v] < tout[u]; }

int Lca(int a, int b) {
  if (A(a, b)) {
    return a;
  }
  if (A(b, a)) {
    return b;
  }
  for (int i = cLogn; i >= 0; --i) {
    if (!A(up[a][i], b)) {
      a = up[a][i];
    }
  }
  return up[a][0];
}

void Count(int v, int ancestor, int& answer) {
  if (v == ancestor) {
    return;
  }
  answer += 1;
  return Count(up[v][0], ancestor, answer);
}

int main() {
  std::cin >> n;

  up.resize(n);
  for (int i = 0; i != n; ++i) {
    up[i].resize(cLogn + 1);
  }

  g.resize(n);
  int u;
  int v;
  for (int i = 0; i != n - 1; ++i) {
    std::cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  tin.resize(n);
  tout.resize(n);
  h.resize(n, 0);

  Dfs(0);

  int q;
  std::cin >> q;
  for (int i = 0; i != q; ++i) {
    std::cin >> v >> u;
    v--;
    u--;
    int ancestor = Lca(v, u);
    int answer;
    if (A(u, v)) {
      answer = h[v] - h[u];
    } else if (A(v, u)) {
      answer = h[u] - h[v];
    } else {
      answer = (h[v] - h[ancestor]) + (h[u] - h[ancestor]);
    }

    std::cout << answer << "\n";
  }
}
