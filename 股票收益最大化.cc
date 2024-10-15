#include <iostream>
#include <vector>
#include <functional>

int solution(std::vector<int> stocks) {
#if 0
    // 第一版代码：单纯的 DFS，不加记忆化，可以想见，效率很低
    // Please write your code here
    // 本题基本可以看出是类似 DP 的问题，我们可以先用 DFS 方法进行自顶向下的递归求解
    // 定义这样的递归函数：
    // dfs(i, hold, frozen)
    // 解释一下含义：代表的是
    // 前 i 天进行股票操作，结束在第 i 天时，手上 hold(true 代表持有，false 代表不持有) 股票
    // 并且 frozen(true 代表处于，false 代表不处于) 冷冻期的情况下，能够拿到的最大利润
    // 那么，我们可以考虑一下如何进行概念上的结果递推
    // dfs(i, true, true)：第 i 天时，手上持有股票，并且处于冷冻期
    // 此时我们可以直接由前一天推断得来：
    // 即：前一天手上持有股票，或者前一天手上不持有股票，并且前一天没处于冷冻期两种情况递推而来
    // 具体的：dfs(i, true, true) = max(dfs(i-1. false, false)-stocks[i-1], dfs(i-1, true, true))
    // 依次类推：
    // dfs(i, true, false) 无意义，因为如果此时手中持有股票，原则上一定是处于冷冻期的，这个值不需要考虑，可以合并到上面的情况中
    // dfs(i, false, true) = dfs(i-1, true, true)+stocks[i-1]：如果第 i 天时手上不持有股票，并且处于冷冻期，那么只可能从前一天结束时手上持有股票，并且处于冷冻期这一种情况递推而来
    // dfs(i, false, false) = max(dfs(i-1, false, true), dfs(i-1, false, false))
    std::function<int(int, bool, bool)> dfs = [&](int i, bool hold, bool frozen) -> int
    {
        // 考虑边界情况：
        // i == 1，那么我们只有一天可用
        if(i == 1)
        {
            // 需要分 hold 与否决定返回数据
            return hold ? -stocks[0] : 0;
        }
        // 其它情况下，可以按照上面的逻辑进行递归求解
        if(hold) 
        {
            return std::max(dfs(i-1, false, false)-stocks[i-1], dfs(i-1, true, true));
        }
        if(frozen)
        {
            return dfs(i-1, true, true)+stocks[i-1];
        }
        return std::max(dfs(i-1, false, true), dfs(i-1, false, false));
    };
    // 我们最终的结果应该是：前 stocks.size() 天时，最后一天处于：
    // 1. 不持有股票，且不处于冷冻期
    // 2. 不持有股票，且处于冷冻期
    // 3. 持有股票，且处于/不处于冷冻期
    // 三种状态下的最大利润值
    // 其实可以想到情况3不可能拿到最大结果
    return std::max(dfs(stocks.size(), false, false), dfs(stocks.size(), false, true));
#endif
#if 0
    // 第二版代码：DFS 带上记忆化
    // Please write your code here
    // 本题基本可以看出是类似 DP 的问题，我们可以先用 DFS 方法进行自顶向下的递归求解
    // 定义这样的递归函数：
    // dfs(i, hold, frozen)
    // 解释一下含义：代表的是
    // 前 i 天进行股票操作，结束在第 i 天时，手上 hold(true 代表持有，false 代表不持有) 股票
    // 并且 frozen(true 代表处于，false 代表不处于) 冷冻期的情况下，能够拿到的最大利润
    // 那么，我们可以考虑一下如何进行概念上的结果递推
    // dfs(i, true, true)：第 i 天时，手上持有股票，并且处于冷冻期
    // 此时我们可以直接由前一天推断得来：
    // 即：前一天手上持有股票，或者前一天手上不持有股票，并且前一天没处于冷冻期两种情况递推而来
    // 具体的：dfs(i, true, true) = max(dfs(i-1. false, false)-stocks[i-1], dfs(i-1, true, true))
    // 依次类推：
    // dfs(i, true, false) 无意义，因为如果此时手中持有股票，原则上一定是处于冷冻期的，这个值不需要考虑，可以合并到上面的情况中
    // dfs(i, false, true) = dfs(i-1, true, true)+stocks[i-1]：如果第 i 天时手上不持有股票，并且处于冷冻期，那么只可能从前一天结束时手上持有股票，并且处于冷冻期这一种情况递推而来
    // dfs(i, false, false) = max(dfs(i-1, false, true), dfs(i-1, false, false))
    // 添加一个记忆化数组
    std::vector<std::vector<std::vector<int>>> memo(stocks.size()+1, std::vector<std::vector<int>>(2, std::vector<int>(2, -1)));
    std::function<int(int, bool, bool)> dfs = [&](int i, bool hold, bool frozen) -> int
    {
        // 考虑边界情况：
        // i == 1，那么我们只有一天可用
        if(i == 1)
        {
            // 需要分 hold 与否决定返回数据
            return hold ? -stocks[0] : 0;
        }
        if(memo[i][hold][frozen] != -1)
        {
            return memo[i][hold][frozen];
        }
        // 其它情况下，可以按照上面的逻辑进行递归求解
        if(hold) 
        {
            memo[i][hold][frozen] = std::max(dfs(i-1, false, false)-stocks[i-1], dfs(i-1, true, true));
            return memo[i][hold][frozen];
        }
        if(frozen)
        {
            memo[i][hold][frozen] = dfs(i-1, true, true)+stocks[i-1];
            return memo[i][hold][frozen];
        }
        memo[i][hold][frozen] = std::max(dfs(i-1, false, true), dfs(i-1, false, false));
        return memo[i][hold][frozen];
    };
    // 我们最终的结果应该是：前 stocks.size() 天时，最后一天处于：
    // 1. 不持有股票，且不处于冷冻期
    // 2. 不持有股票，且处于冷冻期
    // 3. 持有股票，且处于/不处于冷冻期
    // 三种状态下的最大利润值
    // 其实可以想到情况3不可能拿到最大结果
    return std::max(dfs(stocks.size(), false, false), dfs(stocks.size(), false, true));
#endif
    // 第三版代码
    // DFS 转 DP
    // 按上面记忆化数组的方式设定一个 DP 数组
    std::vector<std::vector<std::vector<int>>> dp(stocks.size()+1, std::vector<std::vector<int>>(2, std::vector<int>(2, -1)));
    // 设定边界情况
    dp[1][true][true] = dp[1][true][false] = -stocks[0];
    dp[1][false][true] = dp[1][false][false] = 0;
    // 进行基本的递推过程
    for(int i = 2; i <= stocks.size(); ++i)
    {
        for(int hold = 0; hold < 2; ++hold)
        {
            for(int frozen = 0; frozen < 2; ++frozen)
            {
                if(hold)
                {
                    dp[i][true][frozen] = std::max(dp[i-1][false][false]-stocks[i-1], dp[i-1][true][true]);
                }
                else if(frozen)
                {
                    dp[i][false][true] = dp[i-1][true][true]+stocks[i-1];
                }
                else
                {
                    dp[i][false][false] = std::max(dp[i-1][false][true], dp[i-1][false][false]);
                }
            }
        }
    } 
    return std::max(dp[stocks.size()][false][false], dp[stocks.size()][false][true]);
}

int main() {
    // You can add more test cases here
    std::cout << (solution({1, 2}) == 1) << std::endl;
    std::cout << (solution({2, 1}) == 0) << std::endl;
    std::cout << (solution({1, 2, 3, 0, 2}) == 3) << std::endl;
    std::cout << (solution({2, 3, 4, 5, 6, 7}) == 5) << std::endl;
    std::cout << (solution({1, 6, 2, 7, 13, 2, 8}) == 12) << std::endl;
    return 0;
}