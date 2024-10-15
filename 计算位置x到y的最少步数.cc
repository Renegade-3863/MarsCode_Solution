#include <iostream>

int solution(int xPosition, int yPosition) {
  // Please write your code here
  // 从 DP 的角度进行考虑感觉有些复杂，考虑换用贪心思想
  // 我们开头肯定会需要进行加速，当我们加速到某个速度后，我们可能会发现：
  // 剩下的距离，不允许我们继续加速运动了，因为如果我们此时继续加速，我们将没法保证最后一步只走一格
  // 那么我们就在本步上速度减1
  // 之后我们就始终考虑能否保证速度不变了，而不能重新考虑再加速了
  // 规定一个基础速度1，不断地对这个速度进行数值上的操作
  int velocity = 1, steps = 0;
  // 循环结束条件：xPosition 已经达到了 yPositoin (必须是 xPosition ==
  // yPosition)
  while (xPosition != yPosition) {
    // 多走一步
    ++steps;
    xPosition += xPosition < yPosition ? velocity : -velocity;
    // 计算：如果我们从当前位置开始逐一递减，是否可以满足最后一步只走1步
    // 剩下的距离
    int dist = std::abs(yPosition - xPosition);
    // 以当前速度逐一减速，走出的总距离
    int sum = (velocity + 1) * (velocity) / 2;
    // 如果这个总距离大于剩下的距离，那么我们就必须减速了
    if (sum > dist) {
      --velocity;
    }
    // 如果这个总距离小于剩下的距离，那么我们还需要提速
    else if (sum < dist) {
      ++velocity;
    }
    // 否则，我们当前可以不减速，保持原速进入下一步
  }
  return steps;
}

int main() {
    //  You can add more test cases here
    std::cout << (solution(12, 6) == 4) << std::endl;
    std::cout << (solution(34, 45) == 6) << std::endl;
    std::cout << (solution(50, 30) == 8) << std::endl;
    return 0;
}