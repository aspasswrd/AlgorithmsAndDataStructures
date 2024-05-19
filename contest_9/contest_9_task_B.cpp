#include <algorithm>
#include <iostream>
#include <vector>

const int cMaxN = 100'000;

struct DSU {
  DSU(int m) {
    edges.resize(m);
  }

  struct Edge {
    int b;
    int e;
    int w;

    bool operator<(const Edge& other) const { return w < other.w; }
  };

  int Head(int v) { return (parent[v] == v) ? v : parent[v] = Head(parent[v]); }

  void Unite(int a, int b) {
    a = Head(a);
    b = Head(b);
    if (weights[a] > weights[b]) {
      std::swap(a, b);
    }
    weights[b] += weights[a];
    parent[a] = b;
  }

  void Initialize() {
    for (int i = 0; i != cMaxN; ++i) {
      parent[i] = i;
      weights[i] = 1;
    }
  }
  std::vector<Edge> edges;
  int parent[cMaxN];
  int weights[cMaxN];
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;
  DSU g = DSU(m);
  for (auto& [b, e, w] : g.edges) {
    std::cin >> b >> e >> w;
  }
  g.Initialize();
  std::sort(g.edges.begin(), g.edges.end());
  int answer = 0;
  for (auto& [b, e, w] : g.edges) {
    if (g.Head(b) != g.Head(e)) {
      g.Unite(b, e);
      answer += w;
    }
  }
  std::cout << answer;
}