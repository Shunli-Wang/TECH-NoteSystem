// https://leetcode.cn/problems/restore-ip-addresses/

// Carl的递归套路 https://programmercarl.com/%E5%9B%9E%E6%BA%AF%E7%AE%97%E6%B3%95%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html

#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<string> ans;

    bool isValid(string& str, int startIdx, int endIdx) {
        // 其实在判断.255.之间的数字是否合法，闭区间[startIdx, endIdx]
        if (startIdx > endIdx) return false;
        if (str[startIdx] == '0' && startIdx != endIdx) return false; // 开头是0不合法，单独0合法

        int num = 0;
        for (int i=startIdx; i<=endIdx; i++) {
            if (str[i]>'9' || str[i]<'0') return false; // 过滤特殊字符
            num = num*10 + (str[i]-'0'); // 十进制计算
            if (num > 255) return false; // 大于了255返回false
        }
        return true;
    }

    void process(string& str, int startIdx, int potCnt) {
        if (potCnt == 3) { // 点了3个点，判断答案合法性
            if (isValid(str, startIdx, str.size()-1)) {
                ans.push_back(str);
            }
            return;
        }

        for (int i=startIdx; i<str.size(); i++) { // 截取[startIdx, i]闭区间上的子串
            if (isValid(str, startIdx, i)) {
                // 1.先修改串
                str.insert(str.begin()+i+1, '.');
                potCnt++;
                // 2.再进行dfs递归到最底
                process(str, i+2, potCnt); // 因为加了逗号，所以这里是i+2
                // 3.再改回来
                str.erase(str.begin()+i+1);
                potCnt--;
            } else { // 非法结束这个分支
                break;
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        ans.clear();
        process(s, 0, 0);
        return ans;
    }
};

