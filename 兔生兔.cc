
#include <iostream>
#include <vector>

long long solution(int A) {
    // Edit your code here
    // 经典的斐波那契数列问题
    // 使用线性 DP + 空间优化即可
    if(A == 1)
    {
        return 1;
    }
    if(A == 2)
    {
        return 2;
    }
    long dp0 = 1, dp1 = 2;
    for(int i = 2; i <= A; ++i)
    {
        int tmp = dp1;
        dp1 = dp0+dp1;
        dp0 = tmp;
    }
    return dp1;
}

int main() {
    // Add your test cases here
    std::cout << (solution(5) == 8) << std::endl;
    std::cout << (solution(1) == 1) << std::endl;
    std::cout << (solution(15) == 987) << std::endl;
    std::cout << (solution(50) == 20365011074) << std::endl;

    return 0;
}
