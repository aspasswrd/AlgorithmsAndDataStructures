#include <iostream>
#include <vector>

void PrintVec(std::vector<int>& vec) {
  for (int x : vec) {
    std::cout << x << " ";
  }
}

template <typename Iter>
auto Partition(Iter left, Iter right, int pivot) {
  auto it1 = left;
  auto it2 = --right;
  while (it1 <= it2) {
    while (*it1 < pivot) {
      ++it1;
    }
    while (*it2 > pivot) {
      --it2;
    }
    if (it1 >= it2) {
      break;
    }
    std::swap(*it1, *it2);
    ++it1;
    --it2;
  }
  return it2;
}

void InsertionSort(std::vector<int>& vec) {
  int len = (int)vec.size();
  for (int i = 1; i < len; i++) {
    int key = vec[i];
    int jt = i - 1;
    while (jt >= 0 && vec[jt] > key) {
      vec[jt + 1] = vec[jt];
      jt--;
    }
    vec[jt + 1] = key;
  }
}

int FindMed(std::vector<int>& vec) {
  InsertionSort(vec);
  return vec[(vec.size() - 1) / 2];
}

template <typename Iter>
int FindSuperMed(Iter left, Iter right) {
  int size_of_seg = (int)(right - left);
  if (size_of_seg <= 5) {
    std::vector<int> vec(left, right);
    return FindMed(vec);
  }

  int extra = (size_of_seg % 5 == 0) ? 0 : 1;
  std::vector<int> medians(size_of_seg / 5 + extra);

  auto it1 = left;
  auto it2 = left;

  for (int i = 0; i != size_of_seg / 5; ++i) {
    std::advance(it2, 5);
    std::vector<int> trash(it1, it2);
    medians[i] = FindMed(trash);
    it1 = it2;
  }

  if (extra != 0) {
    std::vector<int> trash(it1, right);
    medians[medians.size() - 1] = FindMed(trash);
  }

  return FindSuperMed(medians.begin(), medians.end());
}

template <typename Iter>
void DetQuickSort(Iter left, Iter right) {
  if (right - left > 1) {
    int pivot = FindSuperMed(left, right);
    auto it = Partition(left, right, pivot);
    it++;
    DetQuickSort(left, it);
    DetQuickSort(it, right);
  }
}

int main() {
  int len;
  std::cin >> len;
  std::vector<int> numbers(len);
  for (int i = 0; i != len; ++i) {
    std::cin >> numbers[i];
  }
  DetQuickSort(numbers.begin(), numbers.end());
  PrintVec(numbers);
}
