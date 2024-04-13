#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::set<int>> ggg;
std::vector<bool> used;
std::vector<int> color;
bool flag = false;

std::vector<int> ttt;

void HasCycle(int vvv) {
  if (flag) {
    return;
  }
  if (color[vvv] == 1) {
    flag = true;
    return;
  }
  if (color[vvv] == 0) {
    color[vvv] = 1;
    used[vvv] = true;
    for (int uuu : ggg[vvv]) {
      HasCycle(uuu);
    }
  }
  color[vvv] = 2;
}

void Dfs(int vvv) {
  used[vvv] = true;
  for (int uuu : ggg[vvv]) {
    if (!used[uuu]) {
      Dfs(uuu);
    }
  }
  ttt.push_back(vvv);
}

void TopoSort() {
  for (int vvv = 1; vvv != static_cast<int>(ggg.size()); ++vvv) {
    if (!used[vvv]) {
      HasCycle(vvv);
      if (flag) {
        std::cout << -1;
        exit(0);
      }
    }
  }

  used.clear();
  used.resize(ggg.size(), false);

  for (int vvv = 1; vvv != static_cast<int>(ggg.size()); ++vvv) {
    if (!used[vvv]) {
      Dfs(vvv);
    }
  }

  std::reverse(ttt.begin(), ttt.end());
  for (auto xxx : ttt) {
    std::cout << xxx << " ";
  }
}

int main() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  ggg.resize(nnn + 1);
  used.resize(nnn + 1);
  color.resize(nnn + 1);

  for (int i = 0; i != mmm; ++i) {
    int uuu;
    int vvv;
    std::cin >> uuu >> vvv;
    ggg[uuu].insert(vvv);
  }

  TopoSort();
}
