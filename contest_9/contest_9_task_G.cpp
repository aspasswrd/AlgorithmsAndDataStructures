#include <iostream>
#include <vector>

std::vector<bool> used;
std::vector<int> mt;

bool Dfs(int v, const std::vector<std::vector<int>>& g) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (int u : g[v]) {
    if (mt[u] == -1 || Dfs(mt[u], g)) {
      mt[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int l;
  int r;
  std::cin >> l >> r;

  std::vector<std::vector<int>> g(l);
  used.resize(l, false);
  mt.resize(r, -1);

  int num;
  for (auto& vec : g) {
    while (true) {
      std::cin >> num;
      if (num == 0) {
        break;
      }
      vec.emplace_back(num - 1);
    }
  }

  int count = 0;

  for (int i = 0; i != l; ++i) {
    used.assign(l, false);
    if (Dfs(i, g)) {
      ++count;
    }
  }

  std::cout << count << "\n";

  for (int i = 0; i != r; ++i) {
    if (mt[i] == -1) {
      continue;
    }
    std::cout << mt[i] + 1 << " " << i + 1 << "\n";
  }
}