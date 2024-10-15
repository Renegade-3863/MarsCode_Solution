#include "iostream"
#include <string>

int solution(std::string version1, std::string version2) {
    // Edit your code here
    // 简单的模拟题，我们可以按照点号为分界点依次取出两个版本号中的各个分段序号进行比较
    int m = version1.size(), n = version2.size();
    // 两个整形变量，分别记录两个分段的版本序号
    int num1 = 0, num2 = 0;
    int i = 0, j = 0;
    // 循环进行分序号的比较，退出条件为：两个序列号都比较到了结尾，或者中间已经可以确定两个版本号的大小关系了
    while(i < m || j < n)
    {
        num1 = 0; num2 = 0;
        // 每次取出一对子序号
        while(i < m && version1[i] != '.')
        {
            num1 = num1*10+(version1[i++]-'0');
        }
        // 如果还没到结尾，那么跳过这个点号
        if(i < m)
        {
            ++i;
        }
        while(j < n && version2[j] != '.')
        {
            num2 = num2*10+(version2[j++]-'0');
        }
        // 如果还没到结尾，那么跳过这个点号
        if(j < n)
        {
            ++j;
        }
        // 比较两个值的大小
        // 此时可以确定 version1 < version2，返回-1
        if(num1 < num2)
        {
            return -1;
        }
        // 此时可以确定 version1 > version2，返回1
        else if(num1 > num2)
        {
            return 1;
        }
    }
    // 二者完全相等，返回0
    return 0;
}

int main() {
    // Add your test cases here

    std::cout << (solution("0.1", "1.1") == -1) << std::endl;
    std::cout << (solution("1.0.1", "1") == 1) << std::endl;
    std::cout << (solution("7.5.2.4", "7.5.3") == -1) << std::endl;
    std::cout << (solution("1.0", "1.0.0") == 0) << std::endl;

    return 0;
}
