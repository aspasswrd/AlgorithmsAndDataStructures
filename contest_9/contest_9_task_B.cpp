#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const int cMaxN = 100'000;

class DSU {
 private:
  struct Edge {
    int b;
    int e;
    int w;

    bool operator<(const Edge& other) const { return w < other.w; }
  };

 public:
  DSU(int m) : m(m) {}

  void AddEdge(int b, int e, int w) {
    edges.insert({b, e, w});
  }

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

  int MST() {
    int answer = 0;
    for (auto& [b, e, w] : edges) {
      if (Head(b) != Head(e)) {
        Unite(b, e);
        answer += w;
      }
    }
  }

 private:
  int m;
  std::set<Edge> edges;
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
  for (int i = 0; i != m; ++i) {
    int b;
    int e;
    int w;
    std::cin >> b >> e >> w;
    g.AddEdge(b, e, w);
  }
  g.Initialize();
  std::cout << g.MST();
}