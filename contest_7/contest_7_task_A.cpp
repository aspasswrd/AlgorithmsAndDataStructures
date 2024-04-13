#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::set<int>> ggg;
std::vector<int> answer;
std::vector<bool> used;
std::vector<int> color;
bool flag = false;

int Dfs(int vvv, int ppp = -1) {
  if (vvv == ppp) {
    answer = {vvv};
    return -1;
  }
  if (color[vvv] == 2) {
    return -1;
  }
  if (color[vvv] == 1) {
    return vvv;
  }
  used[vvv] = true;
  color[vvv] = 1;
  for (int uuu : ggg[vvv]) {
    int kkk = Dfs(uuu, vvv);
    if (kkk != -1 && !flag) {
      answer.push_back(vvv);
      if (kkk == vvv) {
        flag = true;
      }
      return kkk;
    }
  }
  color[vvv] = 2;
  return -1;
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

  for (int vvv = 1; vvv <= nnn; ++vvv) {
    if (!used[vvv]) {
      answer.clear();
      color.clear();
      Dfs(vvv);
      if (!answer.empty()) {
        std::cout << "YES\n";
        for (size_t i = 0; i != answer.size(); ++i) {
          std::cout << answer[answer.size() - 1 - i] << " ";
        }
        exit(0);
      }
    }
  }

  std::cout << "NO";
}