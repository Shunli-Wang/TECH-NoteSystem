// https://leetcode.cn/problems/valid-parentheses/
#include<iostream>
#include<stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        // 坑1：头处理，再简单的题也要有
        if (s.size() == 0 || s.size() == 1) {
            return false;
        }
        stack<char> stk;
        char temp;
        for (char r : s) {
            if (r == '(' || r == '{' || r == '[') {
                stk.push(r);
            } else if (r == ')' || r == '}' || r == ']') {
                if (stk.empty()) return false; // 来了一个需要配对，结果栈空了？肯定不对
                temp = stk.top(); stk.pop();
                if (!(r == ')' ? temp == '(' : false || r == '}' ? temp == '{' : false || r == ']' ? temp == '[' : false)) {
                    // 但凡满足1个，都算你匹配上了。
                    return false;
                }
            }
        }
        // 坑2：一直压栈的情况，需要考虑'(('，最后考察栈空为true
        return stk.empty();
    }
};
