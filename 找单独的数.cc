
#include <iostream>
#include <vector>

int solution(std::vector<int> inp) {
    // Edit your code here
    // 经典位运算问题，利用 x ^ x = 0 的特性即可求解
    int n = inp.size(), res = 0;
    for(int i = 0; i < n; ++i)
    {
        res ^= inp[i];
    }
    return res;
}

int main() {
    // Add your test cases here
    
    std::cout << (solution({1, 1, 2, 2, 3, 3, 4, 5, 5}) == 4) << std::endl;
    std::cout << (solution({0, 1, 0, 1, 2}) == 2) << std::endl;
    
    return 0;
}
