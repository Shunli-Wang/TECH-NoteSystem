#include<iostream>
#include<string>
#include<unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> set;
        int cnt = 0;
        int res = 0;
        
        for (int i=0; i < s.size(); i++) {
            set.clear(); // 先进行set清空
            set.insert(s[i]); // 插入首字母，长度置1
            cnt = 1;
            res = max(res, cnt); // ！处理单个字符串' '的特殊情况

            for (int j=i+1; j < s.length(); j++) { // 非重叠位置遍历
                if (set.count(s[j])) {
                    res = max(res, cnt);
                    break;
                } else {
                    set.insert(s[j]);
                    cnt++;
                    res = max(res, cnt);
                }
            }
        }
        return res;
    }
};

// 虽然通过了但是速度非常慢
