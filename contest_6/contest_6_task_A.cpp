#include <cmath>
#include <iostream>
#include <vector>

const long long kInf = static_cast<long long>(std::pow(2, 31));

int main() {
  int num;
  std::cin >> num;
  std::vector<long long> numbers(num);
  for (int i = 0; i != num; ++i) {
    std::cin >> numbers[num - i - 1];
  }

  std::vector<long long> dp(num);
  std::vector<long long> pos(num);
  std::vector<long long> prev(num);

  int length = 0;
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

  std::vector<long long> answer;
  long long position = pos[length];
  while (position != -1) {
    answer.push_back(num - position);
    position = prev[position];
  }

  std::cout << answer.size() << "\n";

  for (auto& coord : answer) {
    std::cout << coord << " ";
  }

  /*long long position = pos[length];
  while (position != -1) {
    answer.push_back(numbers[position]);
    position = prev[position];
  }

  std::cout << answer.size() << "\n";

  for (size_t i = 0; i != answer.size(); ++i) {
    std::cout << answer[answer.size() - i - 1] << " ";
  }*/
}