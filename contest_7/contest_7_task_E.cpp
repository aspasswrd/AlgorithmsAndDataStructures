#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Graph {
 private:
  struct Edge {
    int u = 0;
    int v = 0;
    int index = 0;

    bool operator==(Edge& other) const {
      return (u == other.u && v == other.v);
    }

    bool operator<(const Edge& other) const {
      if (u == other.u) {
        return v < other.v;
      }
      return u < other.u;
    }
  };

 public:
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
    for (int u : g[v]) {
      if (u != p) {
        if (used[u]) {
          d[v] = std::min(d[v], h[u]);
        } else {
          Dfs(u, v);
          d[v] = std::min(d[v], d[u]);
          if (h[v] < d[u]) {
            if (doubles.contains({u, v}) || doubles.contains({v, u})) {
              continue;
            }
            auto iter = e.find({v, u});
            if (iter == e.end()) {
              iter = e.find({u, v});
            }
            answer.push_back(iter->index);
          }
        }
      }
    }
  }
  bool IsUsed(int v) const { return used[v]; }
  std::vector<int> GetSortedAnswer() {
    std::sort(answer.begin(), answer.end());
    return answer;
  }
 private:
  int n;
  int m;
  std::vector<std::set<int>> g;
  std::vector<bool> used;
  std::vector<int> h;
  std::vector<int> d;
  std::set<Edge> e;
  std::vector<int> answer;
  std::set<Edge> doubles;
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
    if (!g.IsUsed(v)) {
      g.Dfs(v);
    }
  }
  auto answer = g.GetSortedAnswer();
  std::cout << answer.size() << "\n";
  for (int index : answer) {
    std::cout << index << " ";
  }
}
