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
    ggg.resize(n + 1);
    used.resize(n + 1);
    hhh.resize(n + 1);
    ddd.resize(n + 1);
  }

  void AddEdge(int u, int v, int i) {
    eee.insert({u, v, i + 1});
    if (ggg[u].contains(v)) {
      doubles.insert({u, v});
      doubles.insert({v, u});
    } else {
      ggg[u].insert(v);
      ggg[v].insert(u);
    }
  }

  void Dfs(int v, int p = -1) {
    used[v] = true;
    if (p == -1) {
      hhh[v] = 0;
    } else {
      hhh[v] = hhh[p] + 1;
    }
    ddd[v] = hhh[v];
    for (int uuu : ggg[v]) {
      if (uuu != p) {
        if (used[uuu]) {
          ddd[v] = std::min(ddd[v], hhh[uuu]);
        } else {
          Dfs(uuu, v);
          ddd[v] = std::min(ddd[v], ddd[uuu]);
          if (hhh[v] < ddd[uuu]) {
            if (doubles.contains({uuu, v}) || doubles.contains({v, uuu})) {
              continue;
            }
            auto iter = eee.find({v, uuu});
            if (iter == eee.end()) {
              iter = eee.find({uuu, v});
            }
            answer.push_back(iter->index);
          }
        }
      }
    }
  }


  int n;
  int m;
  std::vector<std::set<int>> ggg;
  std::vector<bool> used;
  std::vector<int> hhh;
  std::vector<int> ddd;
  std::set<Pair> eee;
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
