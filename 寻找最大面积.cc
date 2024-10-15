#include <iostream>
#include <vector>
#include <stack>

int solution(int n, int array[]) {
    // Edit your code here
    // 本题是类似最大矩形面积的问题
    // 我们可以控制变量
    // 计算以每个元素为最小值的面积的最大值即可
    // 要计算这些面积，我们可以简单使用类似单调栈道方式来计算两个数组
    // left：left[i] 代表以 array[i] 为高的矩形最靠左可以延伸到的下标
    // right: right[i] 代表以 array[i] 为高的矩形最靠右可以延伸到的下标
    std::vector<int> left(n, -1);
    std::vector<int> right(n, n);
    // 使用一个单调栈分别对 left 和 right 进行计算
    std::stack<int> stk = std::stack<int>();
    for(int i = 0; i < n; ++i)
    {
        // 对于 left[i]，我们需要做的是：找出 i 以及它向左可以延伸出的连续最长的高度不小于 array[i] 的位置下标
        while(!stk.empty() && array[stk.top()] >= array[i])
        {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    stk = std::stack<int>();
    for(int i = n-1; i >= 0; --i)
    {
        while(!stk.empty() && array[stk.top()] >= array[i])
        {
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    // 之后我们只需要根据这两个数组进行计算即可
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        res = std::max(res, (right[i]-left[i]-1)*array[i]);
    }
    return res;
}

int main() {
    // Add your test cases here
    
    std::cout << (solution(5, new int[5]{1, 2, 3, 4, 5}) == 9) << std::endl;
    return 0;
}
