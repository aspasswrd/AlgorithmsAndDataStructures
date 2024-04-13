#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Pair {
  int uuu = 0;
  int vvv = 0;
  int number = 0;

  bool operator==(Pair& other) const {
    return (uuu == other.uuu && vvv == other.vvv);
  }

  bool operator<(const Pair& other) const {
    if (uuu == other.uuu) {
      return vvv < other.vvv;
    }
    return uuu < other.uuu;
  }
};

std::vector<std::set<int>> ggg;
std::vector<bool> used;

std::vector<int> hhh;
std::vector<int> ddd;

std::set<Pair> eee;
std::vector<int> answer;

std::set<Pair> doubles;

void Dfs(int vvv, int ppp = -1) {
  used[vvv] = true;
  if (ppp == -1) {
    hhh[vvv] = 0;
  } else {
    hhh[vvv] = hhh[ppp] + 1;
  }
  ddd[vvv] = hhh[vvv];
  for (int uuu : ggg[vvv]) {
    if (uuu != ppp) {
      if (used[uuu]) {
        ddd[vvv] = std::min(ddd[vvv], hhh[uuu]);
      } else {
        Dfs(uuu, vvv);
        ddd[vvv] = std::min(ddd[vvv], ddd[uuu]);
        if (hhh[vvv] < ddd[uuu]) {
          if (doubles.contains({uuu, vvv}) || doubles.contains({vvv, uuu})) {
            continue;
          }
          auto iter = eee.find({vvv, uuu});
          if (iter == eee.end()) {
            iter = eee.find({uuu, vvv});
          }
          answer.push_back(iter->number);
        }
      }
    }
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
    eee.insert({uuu, vvv, i + 1});
    if (ggg[uuu].contains(vvv)) {
      doubles.insert({uuu, vvv});
      doubles.insert({vvv, uuu});
    } else {
      ggg[uuu].insert(vvv);
      ggg[vvv].insert(uuu);
    }
  }

  for (int vvv = 1; vvv != nnn + 1; ++vvv) {
    if (!used[vvv]) {
      Dfs(vvv);
    }
  }

  std::cout << answer.size() << "\n";
  std::sort(answer.begin(), answer.end());
  for (int xxx : answer) {
    std::cout << xxx << " ";
  }
}
