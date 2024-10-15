
#include <iostream>
#include <string>

std::string solution(const std::string &inp) {
  // Edit your code here
  // 最暴力的方案就是用定长的窗口不断地去滑，直到找到重复子部分或者定长窗口长度已经超过了原串长度的一半
  int n = inp.size();
  for (int i = 0; i < n / 2; ++i) {
    // 先判断这个子串的长度是不是原串的因数，如果不是，那不可能是重复节
    if (n % (i + 1)) {
      continue;
    }
    // 获取一个对应长度的子串
    std::string sub = inp.substr(0, i + 1);
    // 针对这个长度进行滑动检查
    int j = i + 1;
    for (; j < n; j += i + 1) {
      std::string tmp = inp.substr(j, i + 1);
      // 如果这个节不等于第一节，直接退出检查即可
      if (tmp != sub) {
        break;
      }
    }
    // 如果能够走到这里并且 j == n，说明已经找到了我们要的那个循环节
    if (j == n) {
      return sub;
    }
  }
  // 理论上不会执行到这一步
  return "";
}

int main() {
    // Add your test cases here
    
    std::cout << (solution("abcabcabcabc") == "abc") << std::endl;
    return 0;
}
