#include <algorithm>
#include <iostream>
#include <vector>

const int cMaxN = 100'000;

int parent[cMaxN];
int weights[cMaxN];

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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;
  int cost;
  std::vector<Edge> edges;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      if (j >= i) {
        std::cin >> cost;
        continue;
      }
      std::cin >> cost;
      edges.emplace_back(i + 1, j + 1, cost);
    }
  }

  for (int i = 0; i != n; ++i) {
    std::cin >> cost;
    edges.emplace_back(0, i + 1, cost);
  }

  Initialize();
  std::sort(edges.begin(), edges.end());
  int answer = 0;
  for (auto& [b, e, w] : edges) {
    if (Head(b) != Head(e)) {
      Unite(b, e);
      answer += w;
    }
  }
  std::cout << answer;
}