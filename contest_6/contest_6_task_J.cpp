#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

const int kBig = (int)std::pow(10, 9) + 7;

long long Count(std::vector<int>& vec) {
  std::unordered_map<int, size_t> last;
  std::vector<long long> dp(vec.size() + 1);
  dp[0] = 1;

  for (size_t i = 1; i != vec.size() + 1; i++) {
    dp[i] = 2 * dp[i - 1] % kBig;
    if (last.find(vec[i - 1]) != last.end()) {
      dp[i] = (dp[i] - dp[last[vec[i - 1]]] + kBig) % kBig;
    }
    last[vec[i - 1]] = (i - 1);
  }

  return dp[vec.size()] - 1;
}

int main() {
  int n0;
  std::cin >> n0;
  std::vector<int> vec(n0);
  for (auto& x : vec) {
    std::cin >> x;
  }
  std::cout << Count(vec) % kBig;
  return 0;
}
