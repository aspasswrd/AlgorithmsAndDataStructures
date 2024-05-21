#include <deque>
#include <iostream>
#include <ranges>
#include <vector>

const int cMaxN = 60'000;

int parent[cMaxN];
int weights[cMaxN];

struct Pair {
  int first = 0;
  int second = 0;

  bool operator==(const Pair& other) const {
    return (first == other.first && second == other.second) ||
           (second == other.first && first == other.second);
  }
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

void HandleQueries([[maybe_unused]] int n, int m, int k) {
  Initialize();

  std::vector<Pair> edges(m);
  for (int i = 0; i != m; ++i) {
    std::cin >> edges[m - i - 1].first >> edges[m - i - 1].second;
  }

  std::string query;
  int u;
  int v;
  std::deque<std::pair<std::string, std::pair<int, int>>> queries;
  for (int i = 0; i != k; ++i) {
    std::cin >> query;
    std::cin >> u >> v;
    queries.emplace_front(query, std::pair(u, v));
  }
  std::vector<std::string> answer;
  for (auto& [q, pair] : queries) {
    if (q == "cut") {
      Unite(pair.first, pair.second);
    }
    if (q == "ask") {
      if (Head(pair.first) == Head(pair.second)) {
        answer.emplace_back("YES");
      } else {
        answer.emplace_back("NO");
      }
    }
  }

  for (const auto& str : std::ranges::reverse_view(answer)) {
    std::cout << str << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  HandleQueries(n, m, k);
}