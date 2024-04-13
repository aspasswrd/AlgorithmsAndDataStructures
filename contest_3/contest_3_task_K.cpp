#include <algorithm>
#include <iostream>
#include <vector>

struct Line {
  int left = 0;
  int right = 0;
  int y_cord = 0;
  int openned = 0;

  Line(int qleft, int qright, int qy_cord, int qopen) {
    left = qleft;
    right = qright;
    y_cord = qy_cord;
    openned = qopen;
  }
};

struct Rectangle {
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;
};

class TwoDScanLine {
 public:
  TwoDScanLine(std::vector<Rectangle>& rects) {
    size_ = 2 * rects.size();
    for (auto& rect : rects) {
      x_cords_.push_back(rect.x1);
      x_cords_.push_back(rect.x2);
      lines_.emplace_back(rect.x1, rect.x2, rect.y1, 1);
      lines_.emplace_back(rect.x1, rect.x2, rect.y2, -1);
    }
    std::sort(x_cords_.begin(), x_cords_.end());
    std::sort(lines_.begin(), lines_.end(),
              [](Line& l1, Line& l2) { return l1.y_cord < l2.y_cord; });
  }

  long long FindIntersectionArea() {
    long long area = 0;
    for (size_t i = 1; i < size_; ++i) {
      int previous = 0;
      int count = 0;
      for (size_t j = 0; j < size_; ++j) {
        if (lines_[j].right <= x_cords_[i - 1] ||
            lines_[j].left >= x_cords_[i]) {
          continue;
        }
        if (count == 0) {
          previous = lines_[j].y_cord;
        }
        count += lines_[j].openned;
        if (count == 0) {
          area += (long long)(lines_[j].y_cord - previous) *
                  (long long)(x_cords_[i] - x_cords_[i - 1]);
        }
      }
    }
    return area;
  }

 private:
  std::vector<Line> lines_;
  std::vector<int> x_cords_;
  size_t size_ = 0;
};

int main() {
  int num;
  std::cin >> num;
  std::vector<Rectangle> rects(num);

  for (auto& rect : rects) {
    std::cin >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
  }

  std::cout << TwoDScanLine(rects).FindIntersectionArea();
}
