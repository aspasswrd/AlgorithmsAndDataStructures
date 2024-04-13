#include <iostream>
#include <vector>

void ShowMatrix(std::vector<std::vector<int>>& matrix) {
  for (size_t i = 0; i != matrix.size(); ++i) {
    for (size_t j = 0; j != matrix[i].size(); ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

struct Pair {
  size_t val1;
  size_t val2;

  Pair(size_t v1, size_t v2) : val1(v1), val2(v2) {}
};

bool operator==(Pair p1, Pair p2) {
  return (p2.val1 == p1.val1 && p2.val2 == p1.val2);
}

std::vector<std::vector<Pair>> LCS(std::vector<int>& vec1,
                                   std::vector<int>& vec2) {
  size_t m0 = vec1.size();
  size_t n0 = vec2.size();

  std::vector<std::vector<int>> lcs(m0 + 1, std::vector<int>(n0 + 1, 0));
  std::vector<std::vector<Pair>> prev(m0 + 1,
                                      std::vector<Pair>(n0 + 1, {0, 0}));

  for (size_t i = 0; i != m0; ++i) {
    for (size_t j = 0; j != n0; ++j) {
      if (vec1[i] == vec2[j]) {
        lcs[i + 1][j + 1] = lcs[i][j] + 1;
        prev[i + 1][j + 1] = {i, j};
      } else {
        if (lcs[i][j + 1] >= lcs[i + 1][j]) {
          lcs[i + 1][j + 1] = lcs[i][j + 1];
          prev[i + 1][j + 1] = {i, j + 1};
        } else {
          lcs[i + 1][j + 1] = lcs[i + 1][j];
          prev[i + 1][j + 1] = {i + 1, j};
        }
      }
    }
  }
  std::cout << lcs[m0][n0] << "\n";
  return prev;
}

void ReturnLcs(std::vector<int>& answer, std::vector<std::vector<Pair>>& prev,
               std::vector<int>& vec, size_t i0, size_t j0) {
  if (i0 == 0 || j0 == 0) {
    return;
  }
  if (prev[i0][j0] == Pair(i0 - 1, j0 - 1)) {
    ReturnLcs(answer, prev, vec, i0 - 1, j0 - 1);
    answer.push_back(vec[i0 - 1]);
  } else {
    if (prev[i0][j0] == Pair(i0 - 1, j0)) {
      ReturnLcs(answer, prev, vec, i0 - 1, j0);
    } else {
      ReturnLcs(answer, prev, vec, i0, j0 - 1);
    }
  }
}

int main() {
  std::vector<int> vec1;
  std::vector<int> vec2;
  std::string s1;
  std::string s2;
  std::cin >> s1 >> s2;

  for (char ch : s1) {
    vec1.push_back(static_cast<int>(ch));
  }

  for (char ch : s2) {
    vec2.push_back(static_cast<int>(ch));
  }

  std::vector<std::vector<Pair>> prev = LCS(vec1, vec2);
  std::vector<int> answer;
  ReturnLcs(answer, prev, vec1, vec1.size(), vec2.size());

  for (size_t i = 0, j = 0; i != vec1.size() && j != answer.size(); i++) {
    if (vec1[i] == answer[j]) {
      std::cout << i + 1 << " ";
      ++j;
    }
  }
  std::cout << "\n";
  for (size_t i = 0, j = 0; i != vec2.size() && j != answer.size(); i++) {
    if (vec2[i] == answer[j]) {
      std::cout << i + 1 << " ";
      ++j;
    }
  }
}
