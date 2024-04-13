#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#define accuracy 6

std::vector<double> GetNoisesPrefSum(int len) {
  std::vector<double> pref_sum(len + 1);
  for (int i = 1; i != len + 1; ++i) {
    double num;
    std::cin >> num;
    pref_sum[i] = pref_sum[i - 1] + log2(num);
  }
  return pref_sum;
}

void AnswerQueries(std::vector<double>& pref_noises, int queries_count) {
  for (int i = 0; i != queries_count; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    double geom = pow(
        2, (pref_noises[right + 1] - pref_noises[left]) / (right - left + 1));
    std::cout << std::fixed << std::setprecision(accuracy) << geom << std::endl;
  }
}

int main() {
  int len;
  std::cin >> len;
  std::vector<double> pref_noises = GetNoisesPrefSum(len);

  int queries_count;
  std::cin >> queries_count;

  AnswerQueries(pref_noises, queries_count);
}
