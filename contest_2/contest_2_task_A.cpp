#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

int main() {
  std::unordered_map<char, char> map = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
  bool flag = false;
  std::string query;
  getline(std::cin, query);
  std::stack<char> psp;
  for (char ch : query) {
    if (psp.empty() || map.contains(ch)) {
      psp.push(ch);
    } else if (map[psp.top()] == ch) {
      psp.pop();
    } else {
      flag = true;
      break;
    }
  }
  if (!psp.empty() || flag) {
    std::cout << "NO";
  } else {
    std::cout << "YES";
  }
}
