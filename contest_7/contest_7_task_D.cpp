#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::set<int>> ggg;
std::vector<std::set<int>> anti_ggg;
std::vector<bool> used;

std::vector<int> ttt;
std::vector<int> component;

void Dfs1(int vvv) {
  used[vvv] = true;
  for (int uuu : ggg[vvv]) {
    if (!used[uuu]) {
      Dfs1(uuu);
    }
  }
  ttt.push_back(vvv);
}

void Dfs2(int vvv) {
  used[vvv] = true;
  component.push_back(vvv);
  for (int uuu : anti_ggg[vvv]) {
    if (!used[uuu]) {
      Dfs2(uuu);
    }
  }
}

int main() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  ggg.resize(nnn + 1);
  anti_ggg.resize(nnn + 1);
  used.resize(nnn + 1);

  for (int i = 0; i != mmm; ++i) {
    int uuu;
    int vvv;
    std::cin >> uuu >> vvv;
    ggg[uuu].insert(vvv);
    anti_ggg[vvv].insert(uuu);
  }

  for (int vvv = 0; vvv != nnn + 1; ++vvv) {
    if (!used[vvv]) {
      Dfs1(vvv);
    }
  }

  used.clear();
  used.resize(nnn + 1, false);

  std::vector<std::vector<int>> all_components;

  for (int i = 0; i != nnn; ++i) {
    int vvv = ttt[nnn - i];
    if (!used[vvv]) {
      Dfs2(vvv);
      std::vector<int> copy = component;
      all_components.push_back(copy);
      component.clear();
      copy.clear();
    }
  }

  std::cout << all_components.size() << "\n";
  std::vector<int> answer(nnn);
  for (size_t i = 0; i != all_components.size(); ++i) {
    for (auto vvv : all_components[i]) {
      answer[vvv - 1] = static_cast<int>(i) + 1;
    }
  }

  for (auto vvv : answer) {
    std::cout << vvv << " ";
  }
}
