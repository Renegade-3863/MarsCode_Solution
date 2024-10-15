#include <iostream>
#include <string>
#include <vector>

int solution(std::string dna1, std::string dna2) {
    // Please write your code here
    // 经典的字符串修改问题，可以使用动态规划解决
    // 这里不再从 DFS 入手，可以直接选择从自底向上的 DP 角度来思考问题
    // 定义 dp[i][j] 代表 dna1 的前 i 个字符组成的前缀串，修改成 dna2 点前 j 个字符组成的前缀串，需要的最小操作步骤数
    // dp[i][j] 有几种可能的修改方式
    // 1. dna1[i-1] == dna2[j-1]，两个结尾处的字符是相等的
    // 那么我们可以先把 dna1 的前 i-1 个字符修改成 dna2 的前 j-1 个字符，之后最后两个字符不动
    // 即：dp[i][j] = dp[i-1][j-1]
    // 或者先把 dna1 的前 i 个字符修改成 dna2 的前 j-1 个字符，之后再添加一个 dna2 的最后一个字符
    // 即：dp[i][j] = dp[i][j-1]+1
    // 或者 dp[i][j] = dp[i-1][j]+1
    // 而我们可以注意到下面的事实：dp[i][j-1] >= dp[i-1][j-1] && dp[i-1][j] >= dp[i-1][j-1]
    // 因而也必有 dp[i][j-1]+1 > dp[i-1][j-1] && dp[i-1][j]+1 > dp[i-1][j-1]
    // 因而此时我们可以只考虑 dp[i-1][j-1] 这一种情况
    // 即：dp[i][j] = dp[i-1][j-1]
    // 2. dna1[i-1] != dna2[j-1]，两个结尾处的字符是不相等的
    // 那么此时上面考虑的三种情况都是需要考虑的
    // dp[i][j] = max(dp[i-1][j-1]+1, dp[i][j-1]+1, dp[i-1][j]+1)
    // 根据这些条件进行递推即可
    int m = dna1.size(), n = dna2.size();
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1, 0));
    // 先设定边界情况
    // 把一个长度为 i 的长子串修改成空串，我们需要做的就是持续删除，那么就是一定需要 i 次
    for(int i = 1; i <= m; ++i)
    {
        dp[i][0] = i;
    }
    // 原理同上
    for(int j = 1; j <= n; ++j)
    {
        dp[0][j] = j;
    }
    // 递推过程
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(dna1[i-1] == dna2[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = std::min(std::min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1])+1;
            }
        }
    }
    return dp[m][n];
}

int main() {
    //  You can add more test cases here
    std::cout << (solution("AGCTTAGC", "AGCTAGCT") == 2) << std::endl;
    std::cout << (solution("AGCCGAGC", "GCTAGCT") == 4) << std::endl;
    return 0;
}