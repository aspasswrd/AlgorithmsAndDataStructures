#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class MinHeap {
 public:
  size_t Size() { return heap_.size(); }

  void Insert(int num, int query) {
    heap_.emplace_back(num, query);
    permutation_[query] = (int)heap_.size() - 1;
    (*this).SiftUp((int)heap_.size() - 1);
  }

  int GetMin() { return heap_[0].first; }

  int ExtractMin() {
    int index = heap_[0].second;
    permutation_.erase(heap_[0].second);
    heap_[0] = heap_.back();
    permutation_[heap_[0].second] = 0;
    heap_.pop_back();
    (*this).SiftDown(0);
    return index;
  }

  void ExtractByQuery(int query) {
    int index = permutation_[query];
    permutation_.erase(query);
    heap_[index] = heap_.back();
    permutation_[heap_[index].second] = index;
    heap_.pop_back();
    (*this).SiftUp(index);
  }

  void Clear() {
    heap_.clear();
    permutation_.clear();
  }

 private:
  std::vector<std::pair<int, int>> heap_;
  std::unordered_map<int, int> permutation_;

  void Swap(int it1, int it2) {
    std::swap(heap_[it1], heap_[it2]);
    permutation_[heap_[it1].second] = it1;
    permutation_[heap_[it2].second] = it2;
  }

  void SiftDown(int it1) {
    while (2 * it1 + 1 < (int)heap_.size()) {
      int left = 2 * it1 + 1;
      int right = 2 * it1 + 2;
      int it2 = left;
      if (right < (int)heap_.size() && heap_[right].first < heap_[left].first) {
        it2 = right;
      }
      if (heap_[it1].first <= heap_[it2].first) {
        break;
      }
      Swap(it1, it2);
      it1 = it2;
    }
  }

  void SiftUp(int it) {
    while (heap_[it].first < heap_[(it - 1) / 2].first) {
      Swap(it, (it - 1) / 2);
      it = (it - 1) / 2;
    }
  }
};

class MaxHeap {
 public:
  size_t Size() { return heap_.size(); }

  void Insert(int num, int query) {
    heap_.emplace_back(num, query);
    permutation_[query] = (int)heap_.size() - 1;
    (*this).SiftUp((int)heap_.size() - 1);
  }

  int GetMax() { return heap_[0].first; }

  int ExtractMax() {
    int index = heap_[0].second;
    permutation_.erase(heap_[0].second);
    heap_[0] = heap_.back();
    permutation_[heap_[0].second] = 0;
    heap_.pop_back();
    (*this).SiftDown(0);
    return index;
  }

  void ExtractByQuery(int query) {
    int index = permutation_[query];
    permutation_.erase(query);
    heap_[index] = heap_.back();
    permutation_[heap_[index].second] = index;
    heap_.pop_back();
    (*this).SiftUp(index);
  }

  void Clear() {
    heap_.clear();
    permutation_.clear();
  }

 private:
  std::vector<std::pair<int, int>> heap_;
  std::unordered_map<int, int> permutation_;

  void Swap(int it1, int it2) {
    std::swap(heap_[it1], heap_[it2]);
    permutation_[heap_[it1].second] = it1;
    permutation_[heap_[it2].second] = it2;
  }

  void SiftDown(int it1) {
    while (2 * it1 + 1 < (int)heap_.size()) {
      int left = 2 * it1 + 1;
      int right = 2 * it1 + 2;
      int it2 = left;
      if (right < (int)heap_.size() && heap_[right].first > heap_[left].first) {
        it2 = right;
      }
      if (heap_[it1].first >= heap_[it2].first) {
        break;
      }
      Swap(it1, it2);
      it1 = it2;
    }
  }

  void SiftUp(int it) {
    while (heap_[it].first > heap_[(it - 1) / 2].first) {
      Swap(it, (it - 1) / 2);
      it = (it - 1) / 2;
    }
  }
};

class FakeMinMaxHeap {
 public:
  void Size() { std::cout << max_heap_.Size() << "\n"; }

  void Insert(int num, int query) {
    max_heap_.Insert(num, query);
    min_heap_.Insert(num, query);
    std::cout << "ok\n";
  }

  void GetMax() {
    if (max_heap_.Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << max_heap_.GetMax() << "\n";
  }

  void GetMin() {
    if (min_heap_.Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << min_heap_.GetMin() << "\n";
  }

  void ExtractMax() {
    if (max_heap_.Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << max_heap_.GetMax() << "\n";
    int query = max_heap_.ExtractMax();
    min_heap_.ExtractByQuery(query);
  }

  void ExtractMin() {
    if (min_heap_.Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << min_heap_.GetMin() << "\n";
    int query = min_heap_.ExtractMin();
    max_heap_.ExtractByQuery(query);
  }

  void Clear() {
    min_heap_.Clear();
    max_heap_.Clear();
    std::cout << "ok\n";
  }
  
 private:
  MaxHeap max_heap_;
  MinHeap min_heap_;

};

void AnswerQueries(int queries_count) {
  FakeMinMaxHeap heap;
  std::string query;
  int num;
  for (int i = 0; i != queries_count; ++i) {
    std::cin >> query;
    if (query == "insert") {
      std::cin >> num;
      heap.Insert(num, i + 1);
    }

    if (query == "get_max") {
      heap.GetMax();
    }

    if (query == "get_min") {
      heap.GetMin();
    }

    if (query == "extract_max") {
      heap.ExtractMax();
    }

    if (query == "extract_min") {
      heap.ExtractMin();
    }

    if (query == "clear") {
      heap.Clear();
    }

    if (query == "size") {
      heap.Size();
    }
  }
}

int main() {
  int queries_count;
  std::cin >> queries_count;

  AnswerQueries(queries_count);
}
