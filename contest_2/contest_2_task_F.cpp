#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class BinaryHeap {
 public:
  size_t Size() { return heap_.size(); }

  void Insert(long long num, int query) {
    heap_.emplace_back(num, query);
    permutation_[query] = (int)heap_.size() - 1;
    (*this).SiftUp((int)heap_.size() - 1);
  }

  long long GetMin() {
    SiftDown(0);
    return heap_[0].first;
  }

  void ExtractMin() {
    permutation_.erase(heap_[0].second);
    heap_[0] = heap_.back();
    permutation_[heap_[0].second] = 0;
    heap_.pop_back();
    (*this).SiftDown(0);
  }

  void DecreaseKey(int query, int delta) {
    int index = permutation_[query];
    heap_[index].first -= delta;
    (*this).SiftUp(index);
  }

  private:
  std::vector<std::pair<long long, int>> heap_;
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

void AnswerQueries(int queries_count) {
  BinaryHeap heap;
  std::string query;
  long long num;
  for (int i = 0; i != queries_count; ++i) {
    std::cin >> query;
    if (query == "insert") {
      std::cin >> num;
      heap.Insert(num, i + 1);
    }

    if (query == "getMin") {
      std::cout << heap.GetMin() << "\n";
    }

    if (query == "extractMin") {
      heap.ExtractMin();
    }

    if (query == "decreaseKey") {
      int query_num;
      std::cin >> query_num;
      int delta;
      std::cin >> delta;
      heap.DecreaseKey(query_num, delta);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int queries_count;
  std::cin >> queries_count;

  AnswerQueries(queries_count);
}
