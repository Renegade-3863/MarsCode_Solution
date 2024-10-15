#include <iostream>
#include <vector>

int solution(int n, int k, std::vector<std::vector<int>> p) {
    // Edit your code here
    // 感觉还是类似 DP 类的问题，先从 DFS 的角度来进行分析
    // 假设有下面的子问题定义：
    // dfs(i) 代表小明要坚持 i 天，所要花费的最少钱数
    // 那么，假设我们此时知道这样的信息：前 i 天可以到达的所有补给站的信息
    // 此时，我们可以这样做出判断：
    // dfs(i) = dfs(i-1) + min(p[k][1]) (for all k in (0, i))
    // 我们不难发现这样的性质，能坚持 i 天，那么我们最少的钱数一定是买来刚好够吃的食物数的
    // 否则这个钱数一定不是最少的，因为我们可以某一次少买这多出来的一份食物
    // 所以，基本的问题就剩下：如何快速定位这个 min(p[k][1])
    // 这个不难用一个标记变量来实现
    // 不过自顶向下的过程可能不是很好维护这个最小值变量，我们考虑直接写 DP 递推方案
#if 0
    std::vector<int> dp(n+1, 0);
    // 边界情况，如果需要0天，那么我们显然不需要买任何食物，这在初始化过程中就已经完成了
    // 递推情况，维护一个最小价格的变量
    int minCost = p[0][1];
    // 标记当前遇到过的最后一个补给站的下标，初始就是日期为0的补给站
    int idx = 0;
    for(int i = 1; i <= n; ++i)
    {
        // 按递推公式进行递推
        dp[i] = dp[i-1]+minCost;
        // 之后，如果今天到了一个新的补给站，就要更新最小价格的补给站价格
        if(idx+1 < k && p[idx+1][0] == i)
        {
            minCost = std::min(minCost, p[++idx][1]);
        }
    }
    return dp[n];
#endif
    // 上面的过程可以进行空间优化，做一下空间优化
    if(n == 0)
    {
        return 0;
    }
    int dp0 = 0, dp1 = 0;
    int minCost = p[0][1], idx = 0;
    for(int i = 1; i <= n; ++i)
    {
        dp1 = dp0+minCost;
        dp0 = dp1;
        if(idx+1 < k && p[idx+1][0] == i)
        {
            minCost = std::min(minCost, p[++idx][1]);
        }
    }
    return dp1;
}

int main() {
    // Add your test cases here
    std::cout << (solution(5, 4, {{0, 2}, {1, 3}, {2, 1}, {3, 2}}) == 7);
    return 0;
}
