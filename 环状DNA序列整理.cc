#include <iostream>
#include <string>
#include <vector>

std::string solution(std::string dna_sequence) {
    // Please write your code here
    // 比较简单暴力的方案是：枚举并记录所有的合法同 offset 碱基序列，然后利用循环比较决断出字典序最小的那一个表示
    std::vector<std::string> board;
    int n = dna_sequence.size();
    for(int i = 0; i < n; ++i)
    {
        board.push_back(dna_sequence);
        // 把当前的字符串整体 "后移" 一位
        char tmp = dna_sequence[0];
        for(int i = 0; i < n; ++i)
        {
            char memo = dna_sequence[(i+1)%n];
            dna_sequence[(i+1)%n] = tmp;
            tmp = memo;
        }
    }
    // 获得了 board 信息，我们就需要按字典序比较，这一步需要 O(n) 的复杂度
    // 只需要不断循环比较 board[0] 位置处的字符串即可
    for(int i = 1; i < n; ++i)
    {
        if(board[i] < board[0])
        {
            std::swap(board[i], board[0]);
        }
    }
    return board[0];
}

int main() {
    // You can add more test cases here
    std::cout << (solution("ATCA") == "AATC") << std::endl;
    std::cout << (solution("CGAGTC") == "AGTCCG") << std::endl;
    std::cout << (solution("TCATGGAGTGCTCCTGGAGGCTGAGTCCATCTCCAGTAG") == "AGGCTGAGTCCATCTCCAGTAGTCATGGAGTGCTCCTGG") << std::endl;
    return 0;
}