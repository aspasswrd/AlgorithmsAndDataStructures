#include <iostream>
#include <vector>

std::vector<int> Merge(const std::vector<int>& v1, const std::vector<int>& v2,
                       int& inversions) {
  std::vector<int> result(v1.size() + v2.size());

  int it = 0;
  int jt = 0;

  while (it != (int)v1.size() || jt != (int)v2.size()) {
    if (jt == (int)v2.size() || (it != (int)v1.size() && v1[it] <= v2[jt])) {
      result[it + jt] = v1[it];
      ++it;
    } else {
      result[it + jt] = v2[jt];
      if (it != (int)v1.size()) {
        inversions += (int)v1.size() - it;
      }
      ++jt;
    }
  }
  return (result);
}

std::vector<int> MergeSort(std::vector<int>& vec, int& inversions) {
  if (vec.size() == 1) {
    return vec;
  }
  auto it1 = vec.begin();
  auto mid = vec.begin();
  advance(mid, vec.size() / 2);

  std::vector<int> first_half(it1, mid);
  std::vector<int> second_half(mid, vec.end());

  vec = Merge(MergeSort(first_half, inversions),
              MergeSort(second_half, inversions), inversions);

  return vec;
}

int main() {
  int num;
  std::cin >> num;
  std::vector<int> test(num);
  for (int i = 0; i != num; ++i) {
    std::cin >> test[i];
  }
  int inversions = 0;
  MergeSort(test, inversions);
  std::cout << inversions << std::endl;
}
