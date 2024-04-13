#include <time.h>

#include <iostream>
#include <vector>

int GenerateRandomPivot(int low, int high) {
  return low + rand() % (high - low + 1);
}

int Partition(std::vector<int>& vec, int left, int right) {
  int pivot_index = GenerateRandomPivot(left, right - 1);
  int pivot = vec[pivot_index];
  int it1 = left;
  int it2 = right - 1;
  while (it1 <= it2) {
    while (vec[it1] < pivot) {
      it1++;
    }
    while (vec[it2] > pivot) {
      it2--;
    }
    if (it1 >= it2) {
      break;
    }
    std::swap(vec[it1++], vec[it2--]);
  }
  return it2;
}

int KOrderStatistics(std::vector<int>& vec, int kth) {
  int left = 0;
  int right = (int)vec.size();
  while (true) {
    if (right - left <= 1) {
      return vec[left];
    }
    int it = Partition(vec, left, right);
    if (kth <= it) {
      right = it + 1;
    } else {
      left = it + 1;
    }
  }
}

int main() {
  srand(time(nullptr));
  int len;
  int kth;
  std::cin >> len >> kth;
  std::vector<int> vec(len);
  std::cin >> vec[0] >> vec[1];

  const int kMagic1 = 123;
  const int kMagic2 = 45;
  const int kMagic3 = 10004321;

  for (int i = 2; i != len; ++i) {
    vec[i] = (vec[i - 1] * kMagic1 + vec[i - 2] * kMagic2) % kMagic3;
  }

  std::cout << KOrderStatistics(vec, kth - 1) << "\n";

  std::sort(vec.begin(), vec.end());
  for (int x : vec) {
    std::cout << x << " ";
  }
}
