// e-maxx dinic
#include <deque>
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

struct Pair {
  Edge* ptr;
  int index;
};

std::vector<std::vector<int>> g;
std::deque<Edge> edges;

std::vector<std::vector<Pair>> edges_ptr;

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
  while (true) {
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

std::vector<bool> used;

void FakeDfs(int v) {
  if (used[v]) {
    return;
  }
  used[v] = true;
  for (auto& edge : edges_ptr[v]) {
    if (edge.ptr->f != edge.ptr->c) {
      FakeDfs(edge.ptr->v);
    }
  }
}

int main() {
  std::cin >> n >> m;

  s = 0;
  t = n - 1;

  g.resize(n);
  d.resize(n);
  ptr.resize(n);
  q.resize(n);
  edges_ptr.resize(n);

  used.resize(n);

  int u;
  int v;
  int c;
  for (int i = 0; i != m; ++i) {
    std::cin >> u >> v >> c;
    u--;
    v--;
    g[u].push_back(static_cast<int>(edges.size()));
    edges.emplace_back(u, v, c, 0);
    edges_ptr[u].emplace_back(&edges.back(), i);
    g[v].push_back(static_cast<int>(edges.size()));
    edges.emplace_back(v, u, 0, 0);
    edges_ptr[v].emplace_back(&edges.back(), i);

    g[v].push_back(static_cast<int>(edges.size()));
    edges.emplace_back(v, u, c, 0);
    edges_ptr[v].emplace_back(&edges.back(), i);
    g[u].push_back(static_cast<int>(edges.size()));
    edges.emplace_back(u, v, 0, 0);
    edges_ptr[u].emplace_back(&edges.back(), i);
  }

  int answer = Dinic();
  std::vector<Pair> cut;
  FakeDfs(0);

  std::vector<bool> used_index(m, false);

  for (int i = 0; i != n; ++i) {
    if (used[i]) {
      for (auto& edge : edges_ptr[i]) {
        if (!used[edge.ptr->v] && edge.ptr->f == edge.ptr->c &&
            !used_index[edge.index]) {
          used_index[edge.index] = true;
          cut.push_back(edge);
        }
      }
    }
  }

  std::cout << cut.size() << " " << answer << "\n";
  for (auto& x : cut) {
    std::cout << x.index + 1 << " ";
  }
}