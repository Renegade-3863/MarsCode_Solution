#include <deque>
#include <iostream>
#include <string>
#include <vector>

std::string solution(int num, std::string data) {
  // 感觉有点类似括号匹配中使用栈的方法
  // 用一个栈存储当前检查过的所有右括号的位置下标，这时这个栈用来计算每个下标位置左边倒向它的骨牌个数
  // 后面这个栈用来存储当前检查过的所有左括号的位置下标，这时这个栈用来计算每个下标位置右边倒向它的骨牌个数
  std::deque<int> st;
  std::vector<int> left(num, 0);
  std::vector<int> right(num, 0);
  for (int i = 0; i < num; ++i) {
    // 进行检查
    // 如果是'.'，就跳过，不进行压栈操作
    // 而如果是'R'，就需要压栈，因为这个 'R'
    // 会把它以及它右边下标处的骨牌都推向下标 i
    // 如果是'L'，那么此时我们需要考虑出栈，因为这个 'L'
    // 会把它以及它左边下标处的所有骨牌都推离下标 i 如果这个时候栈里存在 'R'
    // 都下标，那么这个 'L' 就能和这个 'R'
    // 抵消一次，二者以及二者之间的骨牌就不会被推向 i 了
    if (data[i] == 'R') {
      st.push_back(i);
    } else if (data[i] == 'L') {
      if (!st.empty()) {
        st.pop_back();
      }
    }
    // 更新 left[i]
    // 此时如果 st 栈中存在 'R' 的下标，那么我们需要取最靠左的那个 'R'
    // 的下标，计算出它到 i 到距离，这个距离就是 i 左侧会倒向它的骨牌的个数
    left[i] = (st.empty() ? 0 : i - st.front()) + (data[i] == 'L' ? -1 : 0) + (data[i] == 'R' ? 1 : 0);
  }
  // 重置 st
  st = std::deque<int>();
  for (int i = num - 1; i >= 0; --i) {
    if (data[i] == 'L') {
      st.push_back(i);
    } else if (data[i] == 'R') {
      if (!st.empty()) {
        st.pop_back();
      }
    }
    // 更新 right[i]
    right[i] = (st.empty() ? 0 : st.front() - i) + (data[i] == 'R' ? -1 : 0) +
               (data[i] == 'L' ? 1 : 0);
  }
  // 根据 left 和 right 进行判断即可
  std::string res;
  int cnt = 0;
  for (int i = 0; i < num; ++i) {
    if (left[i] == right[i]) {
      ++cnt;
    }
  }
  if (cnt == 0) {
    return "0";
  }
  int tmp = cnt;
  for (int i = 0; i < num; ++i) {
    if (left[i] == right[i]) {
      res += std::to_string(i + 1) + (--tmp > 0 ? " " : "");
    }
  }
  res = std::to_string(cnt) + " " + res;
  return res;
}

int main() {
  //  You can add more test cases here
  std::cout << (solution(14, ".L.R...LR..L..") == "4 3 6 13 14") << std::endl;
  std::cout << (solution(5, "R....") == "0") << std::endl;
  std::cout << (solution(1, ".") == "1 1") << std::endl;
  std::cout << (solution(0, "") == "0") << std::endl;
  return 0;
}