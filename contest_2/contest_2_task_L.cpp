#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

struct QueueWithMaximum {
  std::stack<std::pair<int, int>> in;
  std::stack<std::pair<int, int>> out;

  void Clear() {
    while (!in.empty()) {
      in.pop();
    }
    while (!out.empty()) {
      out.pop();
    }
  }

  void Enqueue(int num) {
    if (in.empty()) {
      in.emplace(num, num);
    } else {
      in.emplace(num, std::max(num, in.top().second));
    }
  }

  [[nodiscard]] size_t Size() const {
    size_t answer = in.size() + out.size();
    return answer;
  }

  void Front() {
    if (out.empty()) {
      while (!in.empty()) {
        int num = in.top().first;
        in.pop();
        if (out.empty()) {
          out.emplace(num, num);
        } else {
          out.emplace(num, std::max(num, out.top().second));
        }
      }
    }
  }

  void Dequeue() {
    Front();
    out.pop();
  }

  int GetMax() {
    if (in.empty()) {
      return out.top().second;
    }
    if (out.empty()) {
      return in.top().second;
    }
    return std::max(out.top().second, in.top().second);
  }
};

void ChangeZ(std::vector<std::vector<std::vector<int>>>& matrix, int x_0,
             int y_0, int z_0, int h_0) {
  for (int x0 = 0; x0 != x_0; ++x0) {
    for (int y0 = 0; y0 != y_0; ++y0) {
      QueueWithMaximum queue;
      int it = 0;
      for (int z0 = 0; z0 != z_0; ++z0) {
        queue.Enqueue(matrix[x0][y0][z0]);
        if ((int)queue.Size() == h_0) {
          matrix[x0][y0][it++] = queue.GetMax();
          queue.Dequeue();
        }
      }
      while (queue.Size() != 0) {
        matrix[x0][y0][it++] = queue.GetMax();
        queue.Dequeue();
      }
    }
  }
}

void ChangeY(std::vector<std::vector<std::vector<int>>>& matrix, int x_0,
             int y_0, int z_0, int w_0) {
  for (int x0 = 0; x0 != x_0; ++x0) {
    for (int z0 = 0; z0 != z_0; ++z0) {
      QueueWithMaximum queue;
      int it = 0;
      for (int y0 = 0; y0 != y_0; ++y0) {
        queue.Enqueue(matrix[x0][y0][z0]);
        if ((int)queue.Size() == w_0) {
          matrix[x0][it++][z0] = queue.GetMax();
          queue.Dequeue();
        }
      }
      while (queue.Size() != 0) {
        matrix[x0][it++][z0] = queue.GetMax();
        queue.Dequeue();
      }
    }
  }
}

void ChangeX(std::vector<std::vector<std::vector<int>>>& matrix, int x_0,
             int y_0, int z_0, int l_0) {
  for (int y0 = 0; y0 != y_0; ++y0) {
    for (int z0 = 0; z0 != z_0; ++z0) {
      QueueWithMaximum queue;
      int it = 0;
      for (int x0 = 0; x0 != x_0; ++x0) {
        queue.Enqueue(matrix[x0][y0][z0]);
        if ((int)queue.Size() == l_0) {
          matrix[it++][y0][z0] = queue.GetMax();
          queue.Dequeue();
        }
      }
      while (queue.Size() != 0) {
        matrix[it++][y0][z0] = queue.GetMax();
        queue.Dequeue();
      }
    }
  }
}

void Calculate(std::vector<std::vector<std::vector<int>>>& matrix, int x_0,
               int y_0, int z_0, std::vector<int>& nums) {
  ChangeZ(matrix, x_0, y_0, z_0, nums[2]);
  ChangeY(matrix, x_0, y_0, z_0, nums[1]);
  ChangeX(matrix, x_0, y_0, z_0, nums[0]);
}

int main() {
  int x_0;
  int y_0;
  int z_0;
  std::cin >> x_0 >> y_0 >> z_0;
  std::vector<int> nums(3);
  std::cin >> nums[0] >> nums[1] >> nums[2];
  std::vector<std::vector<std::vector<int>>> matrix(
      x_0, std::vector<std::vector<int>>(y_0, std::vector<int>(z_0)));
  std::unordered_map<int, std::vector<int>> map;
  for (int x0 = 0; x0 != x_0; ++x0) {
    for (int y0 = 0; y0 != y_0; ++y0) {
      for (int z0 = 0; z0 != z_0; ++z0) {
        std::cin >> matrix[x0][y0][z0];
        map[matrix[x0][y0][z0]] = {x0, y0, z0};
      }
    }
  }

  Calculate(matrix, x_0, y_0, z_0, nums);

  int n_0;
  std::cin >> n_0;
  for (int i = 0; i != n_0; ++i) {
    int x_start;
    int y_start;
    int z_start;
    int current;
    std::cin >> x_start >> y_start >> z_start;
    current = matrix[x_start][y_start][z_start];
    while (true) {
      int current_x = map[current][0];
      int current_y = map[current][1];
      int current_z = map[current][2];
      if (current_x + 1 < x_0 &&
          current < matrix[current_x + 1][current_y][current_z]) {
        current = matrix[current_x + 1][current_y][current_z];
      } else if (current_y + 1 < y_0 &&
                 current < matrix[current_x][current_y + 1][current_z]) {
        current = matrix[current_x][current_y + 1][current_z];
      } else if (current_z + 1 < z_0 &&
                 current < matrix[current_x][current_y][current_z + 1]) {
        current = matrix[current_x][current_y][current_z + 1];
      } else {
        std::cout << current_x << " " << current_y << " " << current_z << "\n";
        break;
      }
    }
  }
}