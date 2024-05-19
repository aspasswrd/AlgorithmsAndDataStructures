#include <cmath>
#include <iostream>
#include <vector>

const long long kInf = static_cast<long long>(std::pow(2, 31));

struct Solution {
  Solution(int num, const std::vector<long long>& numbers) : num(num), numbers(numbers) {
    dp.resize(num);
    pos.resize(num);
    prev.resize(num);
  }
  
  void Calculate() {
    pos[0] = -1;
    dp[0] = -kInf;
    for (int i = 1; i != num; ++i) {
      dp[i] = kInf;
    }
    for (int i = 0; i != (num - 1); ++i) {
      int j0 = static_cast<int>(
          std::lower_bound(dp.begin(), dp.end(), numbers[i]) - dp.begin());
      if (dp[j0 - 1] <= numbers[i] && numbers[i] <= dp[j0]) {
        dp[j0] = numbers[i];
        pos[j0] = i;
        prev[i] = pos[j0 - 1];
        length = std::max(length, j0);
      }
    }
  }
  
  std::vector<long long> GetAnswer() {
    std::vector<long long> answer;
    long long position = pos[length];
    while (position != -1) {
      answer.push_back(num - position);
      position = prev[position];
    }
    return answer;
  }
  
  int num;
  int length = 0;
  std::vector<long long> numbers;
  std::vector<long long> dp;
  std::vector<long long> pos;
  std::vector<long long> prev;
};

int main() {
  int num;
  std::cin >> num;
  std::vector<long long> numbers(num);
  for (int i = 0; i != num; ++i) {
    std::cin >> numbers[num - i - 1];
  }
  
  Solution s = Solution(num, numbers);
  s.Calculate();
  auto answer = s.GetAnswer();
  std::cout << answer.size() << "\n";
  for (auto& coord : answer) {
    std::cout << coord << " ";
  }
}
