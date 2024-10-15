#include <functional>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int solution(std::string s) {
  // 规定这样的一个子过程，计算的是表达式 s 从 start
  // 开始的(可能由右括号划定的)同级别子表达式的运算结果
  function<int(const string &, int &)> cal = [&](const string &s,
                                                 int &i) -> int {
    // 基本的逻辑和不带括号的方案基本一致
    char sign = '+';
    int num = 0, n = s.size();
    stack<int> adders;
    // 只做了这一处重构，把重复使用的 switch
    // 语句包装成了一个子过程供大函数调用，简化了冗余部分
    function<void(int &, char &, int &, stack<int> &)> subCal =
        [&](int &num, char &sign, int &i, stack<int> &adders) {
          int prev = adders.empty() ? 0 : adders.top();
          // 这里条件判断和上面是完全一致的
          switch (sign) {
          case '+':
            adders.push(num);
            break;
          case '-':
            adders.push(-num);
            break;
          case '*':
            adders.pop();
            adders.push(prev * num);
            break;
          case '/':
            adders.pop();
            adders.push(prev / num);
            break;
          }
        };
    while (i < n) {
      char c = s[i];
      // 根据当前这个字符的类型决定下一步操作
      // 1. 是一个正常数字，累加到 num 中
      if (isdigit(c)) {
        num = num * 10 + (c - '0');
        // 越过当前位置即可
        ++i;
      }
      // 2. 不是数字，而是一个左括号
      // 此时由于我们假设原表达式是一个正常的运算式，没有被简化，因而这个左括号前面一定有一个符号存在(即使第一个字符就是一个左括号，它的左边也有一个隐性的
      // '+' 号) 因而 num 一定是 0，我们就可以简单地给 num
      // 进行重新赋值，不需要考虑覆盖问题
      else if (c == '(') {
        // 递归计算从下一个位置开始的下一级别的子表达式的结果
        num = cal(s, ++i);
        // 同时，在这个过程中，我们也需要同步修改我们的遍历下标
        // i，避免结束递归后回来又一次检查到这个子表达式
      }
      // 3.
      // 不是数字，而是一个运算符，或者我们已经遍历到了整个表达式的结尾处(注意最后这个位置要么是一个右括号，要么是一个数字字符，不可能是一个运算符)
      // 我们需要把判空格的逻辑也捏到这里，不然逻辑上会有漏洞
      // 在上面这些其它情况下，我们都需要先记录前面的数字结果
      else if (c != ' ') {
        subCal(num, sign, i, adders);
        sign = c;
        num = 0;
        ++i;
        // 我们可以在这里判断 c
        // 是不是一个右括号，如果是，我们就直接退出循环，计算子表达式结果并返回即可
        if (c == ')') {
          break;
        }
      }
      // 4. 是一个空格，此时我们不需要做任何处理，跳过这个空格即可
      else {
        ++i;
      }
    }
    // 第一版的写法有点问题，这里需要带上这个 num 前面的运算符
    // 还是别忘了最后一个加法算子，这个算子我们没有记录到栈中(注意：只有当最后一个字符是数字的时候，我们才会漏掉最后一个算子，如果子表达式的结尾是一个右括号，则不会漏掉)
    // 并且在由右括号退出之前，我们一定会把 num 重制回 0，所以这里可以通过 num
    // 的值来判断我们是不是由右括号退出的循环
    if (num != 0) {
      subCal(num, sign, i, adders);
    }
    int res = 0;
    // 这里的计算方案和前面不带括号的方式是一样的
    while (!adders.empty()) {
      res += adders.top();
      adders.pop();
    }
    return res;
  };
  // 只需要对上面这个运算子过程进行调用即可
  int i = 0;
  return cal(s, i);
}

int main() {
  // You can add more test cases here
  std::cout << (solution("1+1") == 2) << std::endl;
  std::cout << (solution("3+4*5/(3+2)") == 7) << std::endl;
  std::cout << (solution("4+2*5-2/1") == 12) << std::endl;
  std::cout << (solution("(1+(4+5+2)-3)+(6+8)") == 23) << std::endl;
  return 0;
}