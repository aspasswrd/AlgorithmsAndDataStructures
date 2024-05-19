#include <iostream>
#include <queue>
#include <vector>

const int cInf = 2000001;
const int cMagic = 2009000999;

struct Graph {
  Graph(int n) {
    g.resize(n);
  }

  void AddEdge(int v, int u, int w) {
    g[v].emplace_back(u, w);
    g[u].emplace_back(v, w);
  }

  std::vector<int> Dijkstra(int s, int n) {
    std::vector<int> d(n, cInf);
    d[s] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        q;
    q.emplace(0, s);
    while (!q.empty()) {
      auto [cur_d, v] = q.top();
      q.pop();
      if (cur_d > d[v]) {
        continue;
      }
      for (const auto& [u, w] : g[v]) {
        if (d[u] > d[v] + w) {
          d[u] = d[v] + w;
          q.emplace(d[u], u);
        }
      }
    }
    return d;
  }
  std::vector<std::vector<std::pair<int, int>>> g;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int comps;
  std::cin >> comps;

  for (int j = 0; j != comps; ++j) {
    int n0;
    int m0;
    std::cin >> n0 >> m0;

    Graph g = Graph(n0);

    for (int i = 0; i != m0; ++i) {
      int v;
      int u;
      int w;
      std::cin >> v >> u >> w;
      g.AddEdge(v, u, w);
    }

    int start;
    std::cin >> start;

    auto answer = g.Dijkstra(start, n0);
    for (const auto& x : answer) {
      if (x < cInf) {
        std::cout << x << " ";
      } else {
        std::cout << cMagic << " ";
      }
    }
    std::cout << "\n";
  }
}