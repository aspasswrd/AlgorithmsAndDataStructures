#include <iostream>

const int kInf = 1e9 + 7;

void MakeArrays(int n0, int** dp, int** prev, int** dist) {
  for (int i = 0; i != 1 << n0; ++i) {
    dp[i] = new int[n0];
    prev[i] = new int[n0];
  }

  for (int i = 0; i != n0; i++) {
    dist[i] = new int[n0];
    for (int j = 0; j != n0; ++j) {
      std::cin >> dist[i][j];
    }
  }

  for (int mask = 0; mask < (1 << n0); mask++) {
    for (int i = 0; i < n0; i++) {
      dp[mask][i] = kInf;
    }
  }
}

void DeleteArrays(int n0, int** dp, int** prev, int** dist) {
  for (int i = 0; i != 1 << n0; ++i) {
    delete[] dp[i];
    delete[] prev[i];
  }
  for (int i = 0; i != n0; ++i) {
    delete[] dist[i];
  }

  delete[] dp;
  delete[] prev;
  delete[] dist;
}

void Calculate(int n0, int** dp, int** prev, int** dist) {
  for (int mask = 2; mask < (1 << n0); mask++) {
    for (int i = 0; i < n0; i++) {
      if ((bool)((mask >> i) & 1)) {
        int mask_without_i = mask ^ (1 << i);
        int memj = 0;
        for (int j = 0; j < n0; j++) {
          if (j != i && (bool)((mask >> j) & 1)) {
            if (dp[mask][i] > dp[mask_without_i][j] + dist[i][j]) {
              memj = j;
            }
            dp[mask][i] =
                std::min(dp[mask][i], dp[mask_without_i][j] + dist[i][j]);
          }
        }
        prev[mask][i] = memj;
      }
    }
  }
}

void Solution(int n0) {
  int** dp = new int*[1 << n0];
  int** prev = new int*[1 << n0];
  int** dist = new int*[n0];
  MakeArrays(n0, dp, prev, dist);

  for (int i = 0; i != n0; ++i) {
    dp[(1 << i)][i] = 0;
  }
  Calculate(n0, dp, prev, dist);

  int ans = kInf;
  int mask = (1 << n0) - 1;
  int last;
  for (int j = 0; j != n0; ++j) {
    for (int i = 0; i < n0; i++) {
      if (dp[mask][i] < ans) {
        last = i;
        ans = dp[mask][i];
      }
    }
  }
  std::cout << ans << "\n";
  while (mask != 0) {
    std::cout << last + 1 << " ";
    int prev_last = last;
    last = prev[mask][last];
    mask = mask ^ (1 << prev_last);
  }
  DeleteArrays(n0, dp, prev, dist);
}

int main() {
  int n0;
  std::cin >> n0;
  Solution(n0);
}