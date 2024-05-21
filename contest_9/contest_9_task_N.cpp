// e-maxx dinic
#include <iostream>
#include <vector>

#define ll long long

const int cInf = 1e9;

struct Edge {
  ll u = 0;
  ll v = 0;
  ll c = 0;
  ll f = 0;
};

ll n;
ll m;
ll s;
ll t;
std::vector<ll> d;
std::vector<ll> ptr;
std::vector<ll> q;

std::vector<std::vector<ll>> g;
std::vector<Edge> edges;

bool Bfs() {
  ll qh = 0;
  ll qt = 0;
  q[qt++] = s;
  d.assign(n, -1);
  d[s] = 0;
  while (qh < qt && d[t] == -1) {
    ll v = q[qh++];
    for (size_t i = 0; i < g[v].size(); ++i) {
      ll id = g[v][i];
      ll to = edges[id].v;
      if (d[to] == -1 && edges[id].f < edges[id].c) {
        q[qt++] = to;
        d[to] = d[v] + 1;
      }
    }
  }
  return d[t] != -1;
}

ll Dfs(ll v, ll flow) {
  if (flow == 0) {
    return 0;
  }
  if (v == t) {
    return flow;
  }
  for (; ptr[v] < static_cast<ll>(g[v].size()); ++ptr[v]) {
    ll id = g[v][ptr[v]];
    ll to = edges[id].v;
    if (d[to] != d[v] + 1) {
      continue;
    }
    ll pushed = Dfs(to, std::min(flow, edges[id].c - edges[id].f));
    if (pushed != 0) {
      edges[id].f += pushed;
      edges[id ^ 1].f -= pushed;
      return pushed;
    }
  }
  return 0;
}

ll Dinic() {
  ll flow = 0;
  for (;;) {
    if (!Bfs()) {
      break;
    }
    ptr.assign(n, 0);
    while (ll pushed = Dfs(s, cInf)) {
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

  ll u;
  ll v;
  ll c;
  for (ll i = 0; i != m; ++i) {
    std::cin >> u >> v >> c;
    u--;
    v--;
    g[u].push_back(static_cast<ll>(edges.size()));
    edges.emplace_back(u, v, c, 0);
    g[v].push_back(static_cast<ll>(edges.size()));
    edges.emplace_back(v, u, 0, 0);
  }

  std::cout << Dinic() << "\n";
  for (const auto& edge : edges) {
    if (edge.c == 0) {
      continue;
    }
    std::cout << edge.f << "\n";
  }
}