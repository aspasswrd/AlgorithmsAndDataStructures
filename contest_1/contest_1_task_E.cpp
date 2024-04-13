#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int num;
  std::cin >> num;
  std::vector<std::pair<int, int>> times(2 * num);
  for (int i = 0; i != 2 * num; ++i) {
    std::cin >> times[i].first;
    times[i].second = 1;
    ++i;
    std::cin >> times[i].first;
    times[i].second = -1;
  }

  std::sort(times.begin(), times.end(),
            [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
              if (p1.first != p2.first) {
                return p1.first < p2.first;
              }
              return p1.second > p2.second;
            });

  int invariant = 0;
  int time_start = 0;
  int time_end;
  std::vector<std::pair<int, int>> result;
  for (auto time : times) {
    if (time_start == 0) {
      time_start = time.first;
    }
    invariant += time.second;
    if (invariant == 0) {
      time_end = time.first;
      result.emplace_back(time_start, time_end);
      time_start = 0;
    }
  }

  std::cout << result.size() << std::endl;
  for (auto pair : result) {
    std::cout << pair.first << " " << pair.second << std::endl;
  }
}
