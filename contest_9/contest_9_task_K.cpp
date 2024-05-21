// e-maxx dinic
#include <iostream>
#include <vector>

const int cInf = 1e9;

struct Edge {
  int u = 0;
  int v = 0;
  int c = 0;
  int f = 0;
};

int n;
int m;
int s;
int t;
std::vector<int> d;
std::vector<int> ptr;
std::vector<int> q;

std::vector<std::vector<int>> g;
std::vector<Edge> edges;

bool Bfs() {
  int qh = 0;
  int qt = 0;
  q[qt++] = s;
  d.assign(n, -1);
  d[s] = 0;
  while (qh < qt && d[t] == -1) {
    int v = q[qh++];
    for (size_t i = 0; i < g[v].size(); ++i) {
      int id = g[v][i];
      int to = edges[id].v;
      if (d[to] == -1 && edges[id].f < edges[id].c) {
        q[qt++] = to;
        d[to] = d[v] + 1;
      }
    }
  }
  return d[t] != -1;
}

int Dfs(int v, int flow) {
  if (flow == 0) {
    return 0;
  }
  if (v == t) {
    return flow;
  }
  for (; ptr[v] < static_cast<int>(g[v].size()); ++ptr[v]) {
    int id = g[v][ptr[v]];
    int to = edges[id].v;
    if (d[to] != d[v] + 1) {
      continue;
    }
    int pushed = Dfs(to, std::min(flow, edges[id].c - edges[id].f));
    if (pushed != 0) {
      edges[id].f += pushed;
      edges[id ^ 1].f -= pushed;
      return pushed;
    }
  }
  return 0;
}

int Dinic() {
  int flow = 0;
  for (;;) {
    if (!Bfs()) {
      break;
    }
    ptr.assign(n, 0);
    while (int pushed = Dfs(s, cInf)) {
      flow += pushed;
    }
  }
  return flow;
}

int main() {
  std::cin >> n >> m;

  s = 0;
  t = n - 1;

  g.resize(n);
  edges.reserve(m);
  d.resize(n);
  ptr.resize(n);
  q.resize(n);

  int u;
  int v;
  int c;
  for (int i = 0; i != m; ++i) {
    std::cin >> u >> v >> c;
    u--;
    v--;
    g[u].push_back(static_cast<int>(edges.size()));
    edges.emplace_back(u, v, c, 0);
    g[v].push_back(static_cast<int>(edges.size()));
    edges.emplace_back(v, u, 0, 0);
  }

  std::cout << Dinic();
}