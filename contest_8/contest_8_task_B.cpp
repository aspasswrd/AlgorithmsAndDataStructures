#include <iostream>
#include <queue>
#include <vector>

#define ll long long

const ll cInf = 2000000000000000000;

std::vector<ll> Dijkstra(const std::vector<std::vector<std::pair<ll, ll>>>& g,
                         ll s, ll n) {
  std::vector<ll> d(n, cInf);
  d[s] = 0;
  std::priority_queue<std::pair<ll, ll>, std::vector<std::pair<ll, ll>>,
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  ll n0;
  ll m0;
  ll k;
  std::cin >> n0 >> m0 >> k;

  std::vector<ll> infects(k);

  for (ll i = 0; i != k; ++i) {
    std::cin >> infects[i];
  }

  std::vector<std::vector<std::pair<ll, ll>>> g(n0);

  for (ll i = 0; i != m0; ++i) {
    ll v;
    ll u;
    ll w;
    std::cin >> v >> u >> w;
    v -= 1;
    u -= 1;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  ll start;
  ll end;
  std::cin >> start >> end;
  start--;
  end--;

  auto dist = Dijkstra(g, end, n0);
  for (ll i = 0; i != k; ++i) {
    if (dist[infects[i] - 1] <= dist[start]) {
      dist[start] = -1;
      break;
    }
  }
  std::cout << dist[start];
}