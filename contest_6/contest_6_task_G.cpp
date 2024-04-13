#include <deque>
#include <iostream>
#include <vector>

const int kMagic = 10000;

void Calculate(std::vector<std::vector<int>>& dp, std::vector<int>& nums) {
  for (size_t i = 1; i != dp.size(); ++i) {
    dp[i][0] = dp[i - 1][0];
    dp[i][1] = dp[i - 1][1];
    if (nums[i] > nums[i - 1]) {
      dp[i][0] = dp[i - 1][1] + 1;
    } else if (nums[i] < nums[i - 1]) {
      dp[i][1] = dp[i - 1][0] + 1;
    }
  }
}

void MaxAlternatingSubsequence(std::vector<int>& nums) {
  std::vector<std::vector<int>> dp(nums.size(), std::vector<int>(2, 1));
  Calculate(dp, nums);
  int prev = 1;
  if (dp[dp.size() - 1][0] > dp[dp.size() - 1][1]) {
    prev = 0;
  }
  int ans = dp[dp.size() - 1][prev];
  std::deque<int> answer;
  std::cout << ans << "\n";
  size_t i0 = nums.size() - 1;
  while (i0 != 0) {
    if (prev == 1) {
      while (i0 != 0 && dp[i0][1] == dp[i0 - 1][1]) {
        --i0;
      }
      if (i0 == 0) {
        continue;
      }
      answer.push_front(nums[i0]);
      --i0;
      prev = 0;
      continue;
    }
    answer.push_front(nums[i0]);
    while (dp[i0][0] == dp[i0 - 1][0]) {
      --i0;
    }
    --i0;
    prev = 1;
  }
  answer.push_front(nums[0]);
  if ((int)answer.size() != ans) {
    std::cout << answer[answer.size() + kMagic];
  }
  for (int x : answer) {
    std::cout << x << " ";
  }
}
int main() {
  int n0;
  std::cin >> n0;
  std::vector<int> nums(n0);
  for (auto& x : nums) {
    std::cin >> x;
  }
  MaxAlternatingSubsequence(nums);
  return 0;
}