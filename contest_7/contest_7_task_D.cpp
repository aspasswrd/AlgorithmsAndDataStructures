#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Graph {
  Graph(int n, int m) : n(n), m(m) {
    g.resize(n + 1);
    anti_g.resize(n + 1);
    used.resize(n + 1);
  }
  
  void AddEdge(int u, int v) {
    g[u].insert(v);
    anti_g[v].insert(u);
  }
  
  void Dfs1(int vvv) {
    used[vvv] = true;
    for (int uuu : g[vvv]) {
      if (!used[uuu]) {
        Dfs1(uuu);
      }
    }
    t.push_back(vvv);
  }
  
  void Dfs2(int vvv) {
    used[vvv] = true;
    component.push_back(vvv);
    for (int uuu : anti_g[vvv]) {
      if (!used[uuu]) {
        Dfs2(uuu);
      }
    }
  }
  
  void FindComponents() {
    for (int v = 0; v != n + 1; ++v) {
      if (!used[v]) {
        Dfs1(v);
      }
    }
    used.assign(n + 1, false);
    for (int i = 0; i != n; ++i) {
      int v = t[n - i];
      if (!used[v]) {
        Dfs2(v);
        std::vector<int> copy = component;
        all_components.push_back(copy);
        component.clear();
        copy.clear();
      }
    }
  }
  
  std::vector<int> GetAnswer() {
    std::vector<int> answer(n);
    for (size_t i = 0; i != all_components.size(); ++i) {
      for (auto vvv : all_components[i]) {
        answer[vvv - 1] = static_cast<int>(i) + 1;
      }
    }
    return answer;
  }
  
  int n;
  int m;
  std::vector<std::set<int>> g;
  std::vector<std::set<int>> anti_g;
  std::vector<bool> used;
  
  std::vector<int> t;
  std::vector<int> component;
  std::vector<std::vector<int>> all_components;
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph g = Graph(n, m);
  for (int i = 0; i != m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g.AddEdge(u, v);
  }
  g.FindComponents();
  std::cout << g.all_components.size() << "\n";
  auto answer = g.GetAnswer();
  for (auto vvv : answer) {
    std::cout << vvv << " ";
  }
}
