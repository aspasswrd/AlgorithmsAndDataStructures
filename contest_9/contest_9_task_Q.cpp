// algorithmica Dijkstra
#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <set>
#include <vector>

#define ll long long

struct Flow {
  struct Edge {
    ll v = 0;
    ll to = 0;
    ll capacity = 0;
    ll flow = 0;
    ll cost = 0;
  };

  explicit Flow(ll n) : n(n) {
    g.resize(n);
    parent.resize(n);
    d0.resize(n, cInf);
    pot.resize(n, cInf);
  }

  void AddEdge(ll v, ll u, ll c, ll cost) {
    g[v].push_back(static_cast<ll>(edges.size()));
    edges.push_back({v, u, c, 0, cost});
    g[u].push_back(static_cast<ll>(edges.size()));
    edges.push_back({u, v, 0, 0, -cost});
  }

  void Dijkstra() {
    for (ll i = 0; i != n; ++i) {
      d0[i] = cInf;
      parent[i] = -1;
    }
    d0[0] = 0;
    std::set<std::pair<ll, ll>> q0;
    q0.insert({0, 0});
    while (!q0.empty()) {
      ll v = q0.begin()->second;
      q0.erase(q0.begin());
      for (const auto& ind : g[v]) {
        auto& edge = edges[ind];
        if (edge.flow == edge.capacity) {
          continue;
        }
        if (d0[edge.to] > d0[v] + edge.cost) {
          q0.erase({d0[edge.to], edge.to});
          d0[edge.to] = d0[v] + edge.cost;
          max_addable_flow = std::min(max_addable_flow, edge.capacity - edge.flow);
          parent[edge.to] = ind;
          q0.insert({d0[edge.to], edge.to});
        }
      }
    }
  }

  ll BuildFlow() {
    max_addable_flow = cInf;
    Dijkstra();
    if (d0[n - 1] == cInf) {
      return 0;
    }
    ll v = n - 1;
    while (v != 0) {
      auto& id = parent[v];
      edges[id].flow += max_addable_flow;
      edges[id ^ 1].flow -= max_addable_flow;
      v = edges[id].v;
    }
    return max_addable_flow * d0[n - 1];
  }

  ll GetAnswer() {
    ll answer = 0;
    ll temp = BuildFlow();
    while (temp > 0) {
      answer += temp;
      temp = BuildFlow();
    }
  }

  const ll cInf = 1e18;
  ll n;
  ll max_addable_flow = cInf;
  std::vector<ll> d0;
  std::vector<ll> pot;
  std::vector<ll> parent;
  std::vector<Edge> edges;
  std::vector<std::vector<ll>> g;
};

int main() {
  ll n;
  ll m;
  std::cin >> n >> m;

  Flow f = Flow(n);

  ll v;
  ll u;
  ll c;
  ll cost;
  for (ll i = 0; i != m; ++i) {
    std::cin >> v >> u >> c >> cost;
    v--;
    u--;
    f.AddEdge(v, u, c, cost);
  }

  std::cout << f.GetAnswer();
}
