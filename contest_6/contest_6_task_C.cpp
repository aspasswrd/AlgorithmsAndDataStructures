#include <iostream>
#include <vector>

const int kInt = 100001;
const int kMagic = 17;

int MinimizeExperiments(int n0, int k0) {
  std::vector<std::vector<int>> dp(k0 + 1, std::vector<int>(n0 + 1, kInt));
  for (int i = 0; i <= k0; ++i) {
    dp[i][0] = 0;
    dp[i][1] = 0;
  }
  for (int i = 1; i <= k0; ++i) {
    for (int j = 2; j <= n0; ++j) {
      int left = 1;
      int right = j;
      while (left <= right) {
        int mid = (left + ((right - left) / 2));
        int break_count = 1 + std::max(dp[i - 1][mid], dp[i][j - mid]);
        dp[i][j] = std::min(dp[i][j], break_count);
        if (dp[i - 1][mid] < dp[i][j - mid]) {
          left = (mid + 1);
        } else {
          right = (mid - 1);
        }
      }
    }
  }
  return dp[k0][n0];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n0;
  int k0;
  std::cin >> n0 >> k0;
  if (k0 == 0 && n0 != 1) {
    std::cout << -1;
    return 0;
  }
  if (k0 == 0 && n0 == 1) {
    std::cout << 0;
    return 0;
  }
  k0 = std::min(k0, kMagic);
  int result = MinimizeExperiments(n0, k0);
  std::cout << result << "\n";
}
