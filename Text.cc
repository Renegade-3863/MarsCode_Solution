#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class WordDistance {
public:
    // 使用异或重载字符串数对的哈希函数
    struct hashFunc {
        size_t operator() (const pair<string, string>& p) {
            return hash<string>()(p.first) ^ hash<string>()(p.second);
        }
    };
    struct EqualFunc {
        bool operator() (const pair<string, string>& p1, const pair<string, string>& p2) 
        {
            return p1.first == p2.first && p1.second == p2.second;
        }
    };
    vector<string> Dict;
    unordered_map<pair<string, string>, int, hashFunc, EqualFunc> memo;
    WordDistance(vector<string>& wordsDict) {
        copy(wordsDict.begin(), wordsDict.end(), this->Dict.begin());
    }
    
    int shortest(string word1, string word2) {
    // 记忆化操作：如果前面已经找到过这对单词的距离，我们直接返回结果即可
    pair<string, string> p = make_pair<string&, string&>(word1, word2);
    if(memo.find(p) != memo.end())
    {
        return memo[p];
    }
    // 这里封装的方法和243题是一样的，都是使用同向双指针
    int res = this->Dict.size();
    int ptr1 = -1, ptr2 = -1, n = this->Dict.size();
    for(int i = 0; i < n; ++i)
    {
        if(this->Dict[i] == word1)
        {
            if(ptr2 != -1)
            {
                res = min(res, ptr1-ptr2);
            }
            ptr1 = i;
        }
        if(this->Dict[i] == word2)
        {
            if(ptr1 != -1)
            {
                res = min(res, ptr2-ptr1);
            }
            ptr2 = i;
        }
    }
    memo[p] = res;
    return res;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */