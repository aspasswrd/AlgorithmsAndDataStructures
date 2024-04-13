#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::set<int>> ggg;
std::vector<bool> used;

std::vector<int> hhh;
std::vector<int> ddd;

std::set<int> answer;

void Dfs(int vvv, int ppp = -1) {
  used[vvv] = true;
  if (ppp == -1) {
    hhh[vvv] = 0;
  } else {
    hhh[vvv] = hhh[ppp] + 1;
  }
  ddd[vvv] = hhh[vvv];
  int child = 0;
  for (int uuu : ggg[vvv]) {
    if (uuu != ppp) {
      if (used[uuu]) {
        ddd[vvv] = std::min(ddd[vvv], hhh[uuu]);
      } else {
        Dfs(uuu, vvv);
        ddd[vvv] = std::min(ddd[vvv], ddd[uuu]);
        if (hhh[vvv] <= ddd[uuu] && ppp != -1) {
          answer.insert(vvv);
        }
        child++;
      }
    }
  }
  if (ppp == -1 && child > 1) {
    answer.insert(vvv);
  }
}

int main() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  ggg.resize(nnn + 1);
  used.resize(nnn + 1);
  hhh.resize(nnn + 1);
  ddd.resize(nnn + 1);

  for (int i = 0; i != mmm; ++i) {
    int uuu;
    int vvv;
    std::cin >> uuu >> vvv;
    ggg[uuu].insert(vvv);
    ggg[vvv].insert(uuu);
  }

  for (int vvv = 1; vvv != nnn + 1; ++vvv) {
    if (!used[vvv]) {
      Dfs(vvv);
    }
  }

  std::cout << answer.size() << "\n";
  for (auto xxx : answer) {
    std::cout << xxx << "\n";
  }
}