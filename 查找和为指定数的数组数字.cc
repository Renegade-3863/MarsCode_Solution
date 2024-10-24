#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

std::vector<int> solution(const std::vector<int>& arr, int target) {
    // write code here
    // 不难的一道哈希表问题
    // 我们保存一个已经检查过的数据表
    unordered_map<int, int> memo;
    // 对数组进行循环检查
    int n = arr.size();
    // 初始化一个答案数组
    vector<int> res(3);
    // 注意，题目要求我们找出的是左下标最小的二元组，这里需要进行额外检查
    for(int i = 0; i < n; ++i)
    {
        if(memo.find(target-arr[i]) != memo.end())
        {
            if(res[0] == 0)
            {
                res[0] = 1;
                res[1] = target-arr[i]; 
                res[2] = arr[i];
            }
            else
            {
                if(memo[res[1]] > memo[target-arr[i]])
                {
                    res[1] = target-arr[i];
                    res[2] = arr[i];
                }
            }
        }
        // 没找到另一半，把当前元素记录到哈希集合中即可
        if(memo.find(arr[i]) == memo.end())
        {
            memo[arr[i]] = i;
        }
    }
    // 循环完成，如果还没找到结果，直接返回 {0, 0, 0}
    if(res[0])
    {
        return res;
    }
    return {0, 0, 0}; // Placeholder
}

int main() {
    auto result1 = solution({1, 2, 4, 7, 11, 15}, 6);
    std::cout << (result1.size() == 3 && result1[0] == 1 && result1[1] == 2 && result1[2] == 4) << std::endl;

    auto result2 = solution({1, 3, 5, 8, 12}, 10);
    std::cout << (result2.size() == 3 && result2[0] == 0 && result2[1] == 0 && result2[2] == 0) << std::endl;

    auto result3 = solution({-10, -3, 0, 4, 5}, 1);
    std::cout << (result3.size() == 3 && result3[0] == 1 && result3[1] == -3 && result3[2] == 4) << std::endl;

    return 0;
}