#include <functional>
#include <iostream>
#include <vector>

int solution(std::vector<std::vector<int>> inputArray) {
  // Please write your code here
  const unsigned long N = 20050;
  // 本题可以使用类似线段树的方式提升区间标记和检查的效率
  // 根据题目的要求，设定一个大小足够的线段树根结点
  struct Node {
    unsigned long left;
    unsigned long right;
    // visited 代表这个区间 [left, right] 是否存在被访问过的值
    // 同时也可以作为懒标记使用
    bool visited;
  } tree[N];
  // 懒更新函数，从 node 结点向下更新左右孩子
  std::function<void(unsigned long)> lazyUpdate = [&](unsigned long p) {
    if (tree[p].visited) {
      // 对当前结点的左右孩子进行更新
      tree[2 * p].visited = true;
      tree[2 * p+1].visited = true;
    }
  };

  // 线段树构建函数，构建 [l, r] 结点
  std::function<void(unsigned long, unsigned long, unsigned long)> build =
      [&](unsigned long p, unsigned long l, unsigned long r) {
        // 利用递归的方式进行构建
        tree[p].left = l;
        tree[p].right = r;
        // 如果已经到了叶子结点，我们就不需要继续递归构建了
        if (l == r) {
          return;
        }
        // 否则，需要递归进行构建
        int mid = ((r - l) >> 1) + l;
        build(2 * p, l, mid);
        build(2 * p + 1, mid + 1, r);
      };
  // 对 [l, r] 区间进行访问
  std::function<void(unsigned long, unsigned long, unsigned long)> modify =
      [&](unsigned long p, unsigned long l, unsigned long r) {
        // 如果这个结点表示的区间完全包含在我们要访问的区间中，那么我们就可以直接对懒标记进行标记，然后返回即可
        if (tree[p].left >= l && tree[p].right <= r) {
          tree[p].visited = true;
          return;
        }
        // 否则，我们需要先进行懒更新
        lazyUpdate(p);
        int mid = ((tree[p].right - tree[p].left) >> 1) + tree[p].left;
        if (l <= mid) {
          modify(2 * p, l, r);
        }
        if (r >= mid + 1) {
          modify(2 * p + 1, l, r);
        }
      };

  // 对 [l, r] 区间进行检查
  std::function<bool(unsigned long, unsigned long, unsigned long)> search =
      [&](unsigned long p, unsigned long l, unsigned long r) -> bool {
    // 否则，如果当前结点包含于我们要搜索的区间中，那么我们直接返回当前结点的
    // visited 字段
    // std::cout << tree[p].left << ", " << tree[p].right << ";" << std::endl;
    if (tree[p].left >= l && tree[p].right <= r) {
      return tree[p].visited;
    }
    // 否则，依然是需要先进行懒更新
    lazyUpdate(p);
    // 之后根据区间覆盖的范围深入进行检查
    int mid = ((tree[p].right - tree[p].left) >> 1) + tree[p].left;
    bool ret = false;
    if (l <= mid) {
    //   std::cout << l << ":left " << mid << std::endl;
      ret = ret || search(2 * p, l, r);
    }
    if (r >= mid + 1) {
    //   std::cout << r << ":right " << mid+1 << std::endl;
      ret = ret || search(2 * p + 1, l, r);
    }
    return ret;
  };

  // 之后，我们可以利用上面的线段树进行求解
  // 先建树
  build(1, 0, 4000);
  // 之后遍历区间数组，进行插入
  int n = inputArray.size();
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    // std::cout << i << std::endl;
    // 如果这个区间中没有被访问过的结点，那么我们可以把这个区间中的点计入
    // 否则不能计入
    if (!search(1, inputArray[i][0], inputArray[i][1])) {
      cnt += inputArray[i][1] - inputArray[i][0] + 1;
    }
    // 对这个区间进行标记
    modify(1, inputArray[i][0], inputArray[i][1]);
  }
  std::cout << "Cnt: " << cnt << std::endl;
  return cnt;
}

int main() {
  //  You can add more test cases here
  std::vector<std::vector<int>> testArray1 = {{1, 4}, {7, 10}, {3, 5}};
  std::vector<std::vector<int>> testArray2 = {{1, 2}, {6, 10}, {11, 15}};

  std::cout << (solution(testArray1) == 7) << std::endl;
  std::cout << (solution(testArray2) == 9) << std::endl;

  return 0;
}