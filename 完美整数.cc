#include <iostream>
#include <vector>

int solution(int x, int y) {
  // Edit your code here
  // 一道比较明显的数位 DP 类问题
  // 我们可以分别求解 [1, x) 之间的完美整数个数和 [x, y] 之间的完美整数个数
  // 之后用两个数值的差值作为答案
  // 至于 [1, x] 之间的完美整数的求解方法，我们可以通过分情况讨论的方式来实现
  // 1. 当前检查的是一组位数小于 x
  // 的数值，那么我们显然可以取到所有位数等于当前个数的值 假设当前数位是 k
  // 个，那么不难发现会有 9 个含有 k 位数的完美整数
  // 分别为：11...1, 22...2, 33...3, 44...4, 55...5, 66...6, 77...7, 88...8, 99...9
  // 2. 当前检查的是一组位数等于 x 的数值，那么我们就需要按 x
  // 本身的数值大小来明确数位个数等于 x 的完美整数有多少个了 也就是：x
  // 本身位于上面列举出的数构成的区间中的哪一个中 先写代码，细节问题写到了再考虑
  // 首先分别计算 x 和 y 的数位个数，在这个过程中连带着判断出二者是否是完美整数
  int digitx = 0, tmpx = x, digx = tmpx % 10;
  bool perfectX = true;
  // 同时也可以计算出对应数位的各个完美整数的值
  int perfectsX[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  while (tmpx) {
    if (tmpx % 10 != digx) {
      perfectX = false;
    }
    tmpx /= 10;
    ++digitx;
    for (int i = 0; i < 9; ++i) {
      perfectsX[i] = perfectsX[i] * 10 + (i + 1);
    }
  }
  // 循环结束后，我们就知道了 x 是否是一个完美整数，以及它的数位个数
  // 同样的方法再算一遍 y
  int digity = 0, tmpy = y, digy = tmpy % 10;
  bool perfectY = true;
  int perfectsY[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  while (tmpy) {
    if (tmpy % 10 != digy) {
      perfectY = false;
    }
    tmpy /= 10;
    ++digity;
    for (int i = 0; i < 9; ++i) {
      perfectsY[i] = perfectsY[i] * 10 + (i + 1);
    }
  }
  // 之后根据 x 的数位个数，计算情况1对应的数字个数
  int cntx = (digitx - 1 > 0 ? digitx - 1 : 0) * 9;
  // 计算情况2对应的数字个数
  // 这里可以使用二分查找进行定位优化
  // 记录：要找的是 perfectsX 中最大的小于 x 的那个值
  int left = 0, right = 8;
  int resX = -1;
  while (left <= right) {
    int mid = ((right - left) >> 1) + left;
    if (perfectsX[mid] >= x) {
      right = mid - 1;
    } else {
      resX = mid;
      left = mid + 1;
    }
  }
  // 循环结束后，我们不难发现，resX 就代表了我们找到的数位个数等于 x
  // 的完美整数个数-1
  cntx += resX + 1;
  // 同样的方法，可以计算 y 的相应个数
  int cnty = (digity - 1 > 0 ? digity - 1 : 0) * 9;
  left = 0;
  right = 8;
  // 注意，这里我们要找的就是最大的不大于 y 的那个值
  int resY = -1;
  while (left <= right) {
    int mid = ((right - left) >> 1) + left;
    if (perfectsY[mid] > y) {
      right = mid - 1;
    } else {
      resY = mid;
      left = mid + 1;
    }
  }
  cnty += (resY + 1);
  // 两个数的差值就是最终结果
  return cnty - cntx;
}

int main() {
    // Add your test cases here

    std::cout << (solution(1, 10) == 9) << std::endl;
    std::cout << (solution(2, 22) == 10) << std::endl;

    return 0;
}
