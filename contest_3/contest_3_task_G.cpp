#include <iostream>
#include <vector>

class TwoDFenwickTree {
private:
    std::vector<std::vector<int>> matrix_;
    int width_ = 0;

public:
    TwoDFenwickTree(const int kWidth) {
        matrix_.resize(kWidth, std::vector<int>(kWidth, 0));
        width_ = kWidth;
    }

    int GetSum(int pos_x, int pos_y) {
        int result = 0;
        for (int i = pos_x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = pos_y; j >= 0; j = (j & (j + 1)) - 1) {
                result += matrix_[i][j];
            }
        }
        return result;
    }

    int GetSum(int x1, int y1, int x2, int y2) {
        int big = GetSum(x2, y2);
        int small = GetSum(x1 - 1, y1 - 1);
        int down = GetSum(x2, y1 - 1);
        int left = GetSum(x1 - 1, y2);
        return big - down - left + small;
    }

    void Add(int pos_x, int pos_y) {
        for (int i = pos_x; i < width_; i = (i | (i + 1))) {
            for (int j = pos_y; j < width_; j = (j | (j + 1))) {
                matrix_[i][j] += 1;
            }
        }
    }
};

void Solution() {
    int width;
    std::cin >> width;
    TwoDFenwickTree tree(width);

    int queries_count;
    std::cin >> queries_count;
    std::string query;

    for (int i = 0; i != queries_count; ++i) {
        std::cin >> query;
        if (query == "ADD") {
            int pos_x;
            int pos_y;
            std::cin >> pos_x >> pos_y;
            tree.Add(pos_x - 1, pos_y - 1);
        }
        if (query == "GET") {
            int x1;
            int y1;
            int x2;
            int y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2) {
                std::swap(x1, x2);
            }
            if (y1 > y2) {
                std::swap(y1, y2);
            }
            std::cout << tree.GetSum(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << "\n";
        }
    }
}

int main() { Solution(); }
