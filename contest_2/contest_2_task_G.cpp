#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#define power 30

struct MaxBinaryHeap {
 private:
  std::vector<uint64_t> heap_;

  void SiftDown(size_t it1, size_t size = 0) {
    while (2 * it1 + 1 < heap_.size() - size) {
      size_t left = 2 * it1 + 1;
      size_t right = 2 * it1 + 2;
      size_t it2 = left;
      if (right < heap_.size() - size && heap_[right] > heap_[left]) {
        it2 = right;
      }
      if (heap_[it1] >= heap_[it2]) {
        break;
      }
      std::swap(heap_[it1], heap_[it2]);
      it1 = it2;
    }
  }

  void SiftUp(size_t it) {
    while (it != 0 && heap_[it] > heap_[(it - 1) / 2]) {
      std::swap(heap_[it], heap_[(it - 1) / 2]);
      it = (it - 1) / 2;
    }
  }

 public:
  size_t Size() { return heap_.size(); }

  void Insert(uint64_t num) {
    heap_.push_back(num);
    (*this).SiftUp(heap_.size() - 1);
  }

  uint64_t GetMax() {
    SiftDown(0);
    return heap_[0];
  }

  void InsertWithExtract(uint64_t num) {
    heap_[0] = num;
    (*this).SiftDown(0);
  }

  void HeapSort() {
    for (size_t i = 0; i != heap_.size(); ++i) {
      std::swap(heap_[0], heap_[heap_.size() - 1 - i]);
      (*this).SiftDown(0, i + 1);
    }
  }

  void PrintHeap() {
    for (size_t i = 0; i != heap_.size(); ++i) {
      std::cout << heap_[i] << " ";
    }
    std::cout << "\n";
  }
};

void Solution(size_t len, size_t kth, uint64_t& a0, uint64_t& x0,
              uint64_t& y0) {
  MaxBinaryHeap heap;
  uint64_t prev = a0;
  uint64_t current;
  for (size_t i = 0; i != len; ++i) {
    current = (x0 * prev + y0) % (uint64_t)pow(2, power);
    prev = current;
    if (heap.Size() < kth) {
      heap.Insert(current);
      continue;
    }
    if (current < heap.GetMax()) {
      heap.InsertWithExtract(current);
    }
  }
  heap.HeapSort();
  heap.PrintHeap();
}

int main() {
  size_t len;
  std::cin >> len;
  size_t kth;
  std::cin >> kth;
  uint64_t a0;
  std::cin >> a0;
  uint64_t x0;
  std::cin >> x0;
  uint64_t y0;
  std::cin >> y0;

  Solution(len, kth, a0, x0, y0);
}
