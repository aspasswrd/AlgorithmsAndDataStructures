#include <cmath>
#include <iostream>
#include <vector>

struct LCA {
  LCA(int n, std::vector<std::vector<int>>& g0) : g(std::move(g0)), n(n) {
    up.resize(n);
    for (int i = 0; i != n; ++i) {
      up[i].resize(cLogn + 1);
      up[i].assign(cLogn + 1, 0);
    }
    tin.resize(n);
    tout.resize(n);
    h.resize(n, 0);
    nearest_ancestor.resize(n);
    deleted.resize(n, false);
    Dfs(0);
  }

  void Dfs(int v, int p = 0) {
    tin[v] = timer++;
    up[v][0] = p;
    nearest_ancestor[v] = p;
    if (v != p) {
      h[v] = h[p] + 1;
    }
    for (int i = 1; i < cLogn; ++i) {
      up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (const auto& x : g[v]) {
      int to = x;
      if (to != p) {
        Dfs(to, v);
      }
    }
    tout[v] = timer++;
  }

  bool A(int u, int v) { return tin[u] <= tin[v] && tin[v] < tout[u]; }

  int GetClosestNotDeleted(int v, int p = -1) {
    if (p != -1) {
      buffer.push_back(p);
    }
    if (!deleted[v]) {
      for (int x : buffer) {
        nearest_ancestor[x] = v;
      }
      buffer.clear();
      return v;
    }
    return GetClosestNotDeleted(nearest_ancestor[v], v);
  }

  int Lca(int x, int y) {
    if (x == y) {
      return GetClosestNotDeleted(x);
    }
    if (A(x, y)) {
      return GetClosestNotDeleted(x);
    }
    if (A(y, x)) {
      return GetClosestNotDeleted(y);
    }
    for (int i = cLogn - 2; i >= 0; --i) {
      if (!A(GetClosestNotDeleted(up[x][i]), y)) {
        x = GetClosestNotDeleted(up[x][i]);
      }
    }
    return GetClosestNotDeleted(nearest_ancestor[x]);
  }

  void Delete(int v) {
    for (auto x : g[v]) {
      nearest_ancestor[x] = nearest_ancestor[v];
      if (deleted[x] && !deleted[v]) {
        Delete(x);
      }
      deleted[v] = true;
    }
  }

  std::vector<int> buffer;
  std::vector<int> nearest_ancestor;
  std::vector<std::vector<int>> g;
  std::vector<std::vector<int>> up;
  std::vector<bool> deleted;
  std::vector<int> tin;
  std::vector<int> tout;
  std::vector<int> h;
  int timer = 0;
  int n = 0;
  const int cLogn = 20;
};

struct Query {
  char c = '?';
  int a = -1;
  int b = -1;
  Query(char c, int a, int b) : c(c), a(a), b(b){};
};

int main() {
  int q;
  std::cin >> q;
  int n = 1;

  std::vector<Query> queries;
  std::vector<std::vector<int>> g(q);
  int last_vertex_index = 0;
  char c;
  int a;
  int b;
  for (int i = 0; i != q; ++i) {
    std::cin >> c;
    if (c == '+') {
      std::cin >> a;
      a--;
      g[a].push_back(++last_vertex_index);
      n += 1;
    }
    if (c == '-') {
      std::cin >> a;
      a--;
      queries.emplace_back(c, a, -1);
    }
    if (c == '?') {
      std::cin >> a >> b;
      a--;
      b--;
      queries.emplace_back(c, a, b);
    }
  }

  LCA lca = LCA(n, g);
  for (const auto& query : queries) {
    if (query.c == '?') {
      std::cout << lca.Lca(query.a, query.b) + 1 << "\n";
    }
    if (query.c == '-') {
      lca.Delete(query.a);
    }
  }
}
