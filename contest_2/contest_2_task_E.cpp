#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> Merge(
    const std::vector<std::pair<int, int>>& v1,
    const std::vector<std::pair<int, int>>& v2, std::vector<int>& answer) {
  std::vector<std::pair<int, int>> result(v1.size() + v2.size());
  size_t it = 0;
  size_t jt = 0;
  int count = 0;
  while (it != v1.size() || jt != v2.size()) {
    if (jt == v2.size() || (it != v1.size() && v1[it].first <= v2[jt].first)) {
      result[it + jt] = v1[it];
      answer[v1[it].second] += count;
      ++it;
    } else {
      result[it + jt] = v2[jt];
      ++count;
      ++jt;
    }
  }
  return (result);
}

std::vector<std::pair<int, int>> MergeSort(
    std::vector<std::pair<int, int>>& vec, std::vector<int>& answer) {
  if (vec.size() == 1) {
    return vec;
  }
  auto it1 = vec.begin();
  auto mid = vec.begin();
  advance(mid, vec.size() / 2);
  std::vector<std::pair<int, int>> first_half(it1, mid);
  std::vector<std::pair<int, int>> second_half(mid, vec.end());

  vec = Merge(MergeSort(first_half, answer), MergeSort(second_half, answer),
              answer);
  return vec;
}

int main() {
  int num;
  std::cin >> num;
  std::vector<std::pair<int, int>> test(num);
  std::vector<int> answer(num);
  for (int i = 0; i != num; ++i) {
    std::cin >> test[i].first;
    test[i].second = i;
  }
  MergeSort(test, answer);

  for (int ans : answer) {
    std::cout << ans << " ";
  }
}
