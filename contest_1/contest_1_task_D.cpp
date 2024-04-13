#include <iostream>
#include <vector>

bool IsPossible(std::vector<long long>& vec, long long amount, long long len) {
  long long x = vec[0];
  long long counter = 1;
  for (int i = 0; i != (int)vec.size(); ++i) {
    if (vec[i] > x + len) {
      ++counter;
      if (counter > amount) {
        break;
      }
      x = vec[i];
    }
  }
  return (counter <= amount);
}

long long BinSearch(std::vector<long long>& vec, long long amount) {
  long long min_len = 0;
  long long max_len = vec[vec.size() - 1] - vec[0];

  while (true) {
    if (min_len == max_len) {
      return min_len;
    }
    long long mid = (max_len + min_len) / 2;

    if (IsPossible(vec, amount, mid)) {
      max_len = mid;
    } else {
      min_len = mid + 1;
    }
  }
}

int main() {
  long long num;
  long long amount;
  std::cin >> num >> amount;
  std::vector<long long> coords(num);
  for (long long i = 0; i != num; ++i) {
    std::cin >> coords[i];
  }
  std::sort(coords.begin(), coords.end());
  std::cout << BinSearch(coords, amount);
  return 0;
}
