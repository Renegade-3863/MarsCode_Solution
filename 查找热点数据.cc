#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

std::string solution(std::vector<int> nums, int k) {
  // 题目要求为找出一组数据中出现次数前 k 多的元素
  // 考虑一种借助数组和哈希表(映射方案)的方法
  // 使用一个大小更小的精简数组存储每种数据出现的次数
  // 使用另一个哈希表来存储数组中的下标和对应元素之间的映射关系
  // 这样我们就可以通过数组下标来快速找到对应元素的出现次数
  // 先进行处理：
  // mapping[i] = j, 其中 i 是数组的下标，j 是其对应的元素值
  // 一个新加入的哈希表，用于添加过程，遇到一个以前出现过的元素，需要用它来反向查找对应的
  // cnts 数组下标
  std::unordered_map<int, int> mapping;
  std::unordered_map<int, int> mapping2;
  // 记录每种元素出现的次数
  std::vector<int> cnts;
  int n = (int)nums.size();
  for (int i = 0; i < n; ++i) {
    // 如果这个元素之前没有被记录过，说明它是一个新元素，我们需要在数组中新建一个项来存储它出现的次数
    // 并在哈希表中记录这个数组下标和这个元素值本身之间的映射关系
    if (mapping2.find(nums[i]) == mapping2.end()) {
      cnts.push_back(1);
      mapping[cnts.size() - 1] = nums[i];
      mapping2[nums[i]] = cnts.size() - 1;
    }
    // 否则，这个元素之前记录过，我们只需要通过哈希表中的记录找到这个计数值对应的数组下标，对其递增即可
    else {
      ++cnts[mapping2[nums[i]]];
    }
  }
  // 这样遍历了一次以后，我们就在 cnts 中记录好了 nums 中所有元素的出现次数
  // 之后，最简单直接的方案，也是最没营养的方案就是直接对 nums
  // 进行排序，再取出前 k 个元素，这会消耗 O(nlogn) 的复杂度 题目要求我们使用
  // O(n) 的复杂度，所以要想办法优化 其实排序也有 O(n)
  // 复杂度的种类，比如桶排序和计数排序，不过这些都需要 O(n) 的额外空间
  // 也不是最优的，而且在数据量较大的情况下，计数排序甚至没法执行
  // 所以我们需要考虑空间效率更高，并且时间复杂度也是渐进 O(n) 的方案
  // 这样可选的方案几乎就只剩下 快速选择 了
  // 基本思路是这样的：
  // 规定一个递归函数，dfs(res, cnts, i, j, k) ：没有返回值，不过 res
  // 是按引用传参 递归函数内部会把 cnts 的 [i, j] 区间内的元素中的前 k
  // 大的元素接到 res 结尾
  // 注意题目不要求返回结果有序，所以这样直接尾接的方案是可行的
  // 写一下具体的逻辑
  std::function<void(std::string &, std::vector<int> &, int, int, int)> dfs =
      [&](std::string &res, std::vector<int> &cnts, int i, int j, int k) {
        // 如果 i > j，说明我们要找的区间中没有元素，可以直接返回
        // 如果 k == 0，说明我们已经找全了数组中前 k 大的元素，可以直接返回
        if (i > j || k <= 0) {
          return;
        }
        // 针对这个区间进行快速选择
        // 生成一个 [i, j] 区间内的随机数作为 pivot
        int pivot = std::rand() % (j - i + 1) + i;
        // 把这个位置上的元素和 j 位置上的元素交换
        std::swap(cnts[pivot], cnts[j]);
        // 之后就是和 partition 一样的操作
        int l = i - 1;
        for (int r = i; r < j; ++r) {
          // 这里个人认为写不写等于号都可以，区别在于如果遇到一组和 pivot
          // 相同的值，我们会把 pivot 值最后放到这一组相同值的最左边还是最右边
          // 带等号的会放到最右边，不带等号的会放到最左边
          if (cnts[r] >= cnts[j]) {
            std::swap(cnts[++l], cnts[r]);
          }
        }
        // 此时 l 就是 pivot 的最终位置，把它和 j 位置上的元素交换
        std::swap(cnts[++l], cnts[j]);
        // 此时 l 的值就是我们前面选出的 pivot 值的排位值
        // 我们可以根据这个值和 k 的关系决定下一步操作
        if (l - i + 1 == k) {
          // 最简单的情况，我们恰好找到了前 k 大的所有元素(都在下标 l+1 左边)
          for (int t = i; t <= l; ++t) {
            // 注意，我们需要根据哈希表记录的映射关系真正找到这个元素本身
            res += std::to_string(mapping[t]);
            if (t != l) {
              res += ",";
            }
          }
          // 此时可以直接返回
          return;
        } else if (l - i + 1 < k) {
          // 如果我们找到的元素排位小于 k，那么说明所有在下标 l+1
          // 左侧的元素都是前 k 大的元素 但还不是所有 k
          // 个都被找到了，不过我们可以先把找到的这 l+1 个进行添加
          for (int t = i; t <= l; ++t) {
            res += std::to_string(mapping[t]);
            res += ",";
          }
          // 之后需要修改 k 值，并向右递归查找
          // 由于我们已经找到了 l+1 个，因而我们在后面剩下的区间中就只需要再找前
          // k-l-1 大的元素即可
          dfs(res, cnts, l + 1, j, k - l - 1);
          // 找到后直接返回即可
          return;
        } else {
          // 如果我们找到的元素排位大于 k，那么此时不能以任何形式明确这前 l+1
          // 个中的元素哪些是要添加的，哪些是不能添加的
          // 所以我们不进行任何添加，只是缩小查找的范围
          dfs(res, cnts, i, l - 1, k);
          return;
        }
      };
  // 对上面的回调函数进行调用
  // 全局的结果字符串
  std::string res = "";
  // 进行调用
  dfs(res, cnts, 0, cnts.size() - 1, k);
  // Please write your code here
  return res;
}

int main() {
  //  You can add more test cases here
  std::vector<int> nums1 = {1, 1, 1, 2, 2, 3};
  std::vector<int> nums2 = {1};

  std::cout << (solution(nums1, 2) == "1,2") << std::endl;
  std::cout << (solution(nums2, 1) == "1") << std::endl;

  return 0;
}