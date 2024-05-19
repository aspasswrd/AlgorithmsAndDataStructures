#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Pair {
  int u = 0;
  int v = 0;
  int index = 0;

  bool operator==(Pair& other) const {
    return (u == other.u && v == other.v);
  }

  bool operator<(const Pair& other) const {
    if (u == other.u) {
      return v < other.v;
    }
    return u < other.u;
  }
};

struct Graph {
  Graph(int n, int m) : n(n), m(m) {
    g.resize(n + 1);
    used.resize(n + 1);
    h.resize(n + 1);
    d.resize(n + 1);
  }

  void AddEdge(int u, int v, int i) {
    e.insert({u, v, i + 1});
    if (g[u].contains(v)) {
      doubles.insert({u, v});
      doubles.insert({v, u});
    } else {
      g[u].insert(v);
      g[v].insert(u);
    }
  }

  void Dfs(int v, int p = -1) {
    used[v] = true;
    if (p == -1) {
      h[v] = 0;
    } else {
      h[v] = h[p] + 1;
    }
    d[v] = h[v];
    for (int uuu : g[v]) {
      if (uuu != p) {
        if (used[uuu]) {
          d[v] = std::min(d[v], h[uuu]);
        } else {
          Dfs(uuu, v);
          d[v] = std::min(d[v], d[uuu]);
          if (h[v] < d[uuu]) {
            if (doubles.contains({uuu, v}) || doubles.contains({v, uuu})) {
              continue;
            }
            auto iter = e.find({v, uuu});
            if (iter == e.end()) {
              iter = e.find({uuu, v});
            }
            answer.push_back(iter->index);
          }
        }
      }
    }
  }


  int n;
  int m;
  std::vector<std::set<int>> g;
  std::vector<bool> used;
  std::vector<int> h;
  std::vector<int> d;
  std::set<Pair> e;
  std::vector<int> answer;
  std::set<Pair> doubles;
};


int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph g = Graph(n, m);
  for (int i = 0; i != m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g.AddEdge(u, v, i);
  }
  for (int v = 1; v != n + 1; ++v) {
    if (!g.used[v]) {
      g.Dfs(v);
    }
  }
  std::cout << g.answer.size() << "\n";
  std::sort(g.answer.begin(), g.answer.end());
  for (int xxx : g.answer) {
    std::cout << xxx << " ";
  }
}
