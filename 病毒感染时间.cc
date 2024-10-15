#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int solution(int row_n, int column_m, std::vector<std::vector<int>> seats,
             std::vector<int> patient) {
  // 添加一个不合法情况检查
  if (patient[0] < 0 || patient[0] >= row_n || patient[1] < 0 ||
      patient[1] >= column_m) {
    return 0;
  }
  // Please write your code here
  // 记录四个方向的数组
  const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  // 模拟类问题，我们可以按时间为轴进行遍历
  // 记录当前还未被感染的人数
  // 因为初始时已经有一个人被感染了，所以这里我们对总数减一个1
  int healthy = row_n * column_m - 1;
  // 记录当前时间，初始是第0秒
  int sec = 0;
  // 这个队列用于记录所有 "和感染者相邻" 的人的坐标
  std::queue<std::pair<int, int>> q;
  // 我们考虑如何定义一个人 "已感染"
  // 健康的人在题目中被定义为 0/1，所以我们肯定不能用这两个值
  // 不过我们似乎可以使用 "被传播强度" 来标记一个人的受感程度
  // 即：它当前的数字和原始数字的值差距
  // 比如一个人原本是 1 (戴口罩的)，那么当他达到 3
  // 时，我们就认为他已经被感染了，此时已经具备了传染能力
  // 这也是我们保留一份基础样板的原因，因为我们需要确认，如果一个人状态是2，那么他是戴口罩的(此时还没被感染)，还是不戴口罩的(此时已经被感染了)
  // 不断进行循环检查，直到健康人数变成0为止
  // 思考：其实不需要真的保存这个过程表本身，我们可以用一个队列保存当前和被感染者相邻的健康人的坐标
  // "和感染者相邻的健康人" 定义为：本身是健康人，并且上下左右存在至少一个感染者
  // 记录一个原表，作为基础样板
  std::vector<std::vector<int>> original = seats;
  // 用于 BFS 记录已经访问过的格子，防止重复访问
  std::vector<std::vector<bool>> visited(row_n,
                                         std::vector<bool>(column_m, false));
  visited[patient[0]][patient[1]] = true;
  // 压入 "与感染者相邻的健康人" 坐标
  for (int k = 0; k < 4; ++k) {
    int nextx = patient[0] + dirs[k][0], nexty = patient[1] + dirs[k][1];
    if (nextx >= 0 && nextx < row_n && nexty >= 0 && nexty < column_m) {
      q.push(std::make_pair<int &, int &>(nextx, nexty));
    }
  }
  while (healthy > 0) {
    // 记录当前所有还是 "和感染者相邻" 的人的个数，进行对应次数遍历
    int n = q.size();
    for (int i = 0; i < n; ++i) {
      // 取出一个队头的位置坐标，从他开始 "被感染"
      auto [x, y] = q.front();
      // 先默认他被感染，弹出队列
      // 视乎结束一轮后他是否还健康来决定是否要把他重新加回队列
      q.pop();
      // 检查四个方向上邻接的坐标上的人
      for (int k = 0; k < 4; ++k) {
        // 先计算出邻接格子的可能坐标
        int nextx = x + dirs[k][0], nexty = y + dirs[k][1];
        // 检查坐标合法性
        if (nextx >= 0 && nextx < row_n && nexty >= 0 && nexty < column_m &&
            visited[nextx][nexty]) {
          // 是一个合法坐标，并且这个人被感染了
          // 由这个感染者对 (x, y) 处的这个健康人进行感染
          ++seats[x][y];
          // 如果感染后，这个健康人也被感染了，那么我们就把他视为感染者，但不把他标记为
          // true，因为此时他还不具备传染能力，这里先不把他周围的人添加到队列中，因为不能确定四周的人是不是最后也会是健康的
        }
      }
      // 把原来的结点压回队尾
      q.push(std::make_pair<int &, int &>(x, y));
    }
    // 一轮循环结束后，我们需要重新检查本层这些原本是健康人的结点，看他们的邻居现在还是不是健康人，如果这些原本是健康人的人变成了感染者，那么我们此时再把和他们相邻的健康人添加到队列中
    // 否则，如果原本是健康人，现在还是健康人，那么不进行额外的添加，把这个人放回队尾即可
    // 记录已经添加过的格子，防止重复添加
    std::vector<std::vector<bool>> added(row_n, std::vector<bool>(column_m, false));
    for (int i = 0; i < n; ++i) {
      auto [x, y] = q.front();
      q.pop();
      // 这个原来的健康人被感染了，就要尝试添加他的几个邻居，基于他们现在是不是感染者
      if ((original[x][y] == 0 && seats[x][y] - original[x][y] >= 1) ||
          (original[x][y] == 1 && seats[x][y] - original[x][y] >= 2) && !visited[x][y]) {
        visited[x][y] = true;
        --healthy;
        for (int k = 0; k < 4; ++k) {
          int nextx = x + dirs[k][0], nexty = y + dirs[k][1];
          if (nextx >= 0 && nextx < row_n && nexty >= 0 && nexty < column_m &&
              !visited[nextx][nexty] && !added[nextx][nexty]) {
            q.push(std::make_pair<int &, int &>(nextx, nexty));
            added[nextx][nexty] = true;
          }
        }
      }
      // 这个原来健康的人现在还是健康的，不需要任何操作，把他压回队尾即可
      else {
        q.push(std::make_pair<int &, int &>(x, y));
      }
    }
    // 上面这一堆是1秒内发生的事情，我们递增时间1秒
    ++sec;
  }
  return sec;
}

int main() {
  //  You can add more test cases here
  std::vector<std::vector<int>> testSeats1 = {
      {0, 1, 1, 1}, {1, 0, 1, 0}, {1, 1, 1, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<int>> testSeats2 = {
      {0, 1, 1, 1}, {1, 0, 1, 0}, {1, 1, 1, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<int>> testSeats3 = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  std::vector<std::vector<int>> testSeats4 = {
      {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
  std::vector<std::vector<int>> testSeats5 = {{1}};

    std::cout << (solution(4, 4, testSeats1, {2, 2}) == 6) << std::endl;
    std::cout << (solution(4, 4, testSeats2, {2, 5}) == 0) << std::endl;
    std::cout << (solution(4, 4, testSeats3, {2, 2}) == 4) << std::endl;
    std::cout << (solution(4, 4, testSeats4, {2, 2}) == 6) << std::endl;
    std::cout << (solution(1, 1, testSeats5, {0, 0}) == 0) << std::endl;

  return 0;
}