#include <iostream>
#include <vector>

using namespace std;

int solution(vector<int> array) {
    // Edit your code here
    // 经典的摩尔投票问题
    // 选择一个变量保存当前的 "候选人"
    int candidate = array[0];
    // cnt 用于记录当前这个 "候选人" 拥有的净票数
    int cnt = 1;
    int n = array.size();
    for(int i = 1; i < n; ++i)
    {
        if(array[i] == candidate)
        {
            ++cnt;
        }
        else
        {
            if(cnt == 0)
            {
                // 当前候选人已经没票了，而最新的一票又不是投给当前候选人的，那么就要更新候选人了
                candidate = array[i];
                ++cnt;
            }
            else
            {
                // 抵消当前候选人的一票
                --cnt;
            }
        }
    }
    // 因为题目保证能够找到这个候选人，所以我们直接返回 candiadte 即可，不用重新检查它的总票数
    return candidate;
}

int main() {
    // Add your test cases here
    
    cout << (solution({1, 3, 8, 2, 3, 1, 3, 3, 3}) == 3) << endl;
    
    return 0;
}