// https://leetcode.cn/problems/basic-calculator-ii
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    /* 自己写的练习版本 */
    // 1. 难点：presign的设置、符号位和结束位判断的设计
    // 1+2*4      1         +       2     *      4
    //          stk.top  presign   cur   s[i]
    int calculate(string s) {
        int len = s.size();
        stack<int> stk;
        char presign = '+';
        int cur = 0;

        for (int i=0; i<len; i++) {
            // 是数字
            if ('0' <= s[i] && s[i] <= '9') {
                cur = cur * 10 + (s[i] - '0');
            }
            // 是符号位 || 来到最后一位结算
            if ((s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/') || i == len-1) {
                if (presign == '+') {
                    stk.push(cur);
                } else if (presign == '-') {
                    stk.push(-1 * cur);
                } else if (presign == '*') {
                    stk.top() = stk.top() * cur;
                } else if (presign == '/') {
                    stk.top() = stk.top() / cur;
                }
                // 更新符号
                presign = s[i];
                cur = 0;
            }
        }

        int ans = 0;
        while (!stk.empty()) {
            ans += stk.top(); stk.pop();
        }
        return ans;
    }

    /* 官方解法 */
    int calculateOff(string s) {
        int len = s.size();
        stack<string> stk;
        int cur = 0;

        char preSign = '+'; // 设置预先符号位，记录上一次的符号

        for (int i=0; i<len; i++) {
            // 是一个单个数字，累乘
            if (isNumber(s[i])) {
                cur = cur * 10 + (s[i] - '0');
            }
            // 是一个操作符号 || 或者来到了最后位置
            if (isOperator(s[i]) || i == len-1) {
                if (preSign == '+') {
                    stk.push(to_string(cur));
                } else if (preSign == '-') {
                    stk.push(to_string(-1 * cur));
                } else if (preSign == '*') {
                    stk.top() = to_string(atoi(stk.top().c_str()) * cur);
                } else if (preSign == '/') {
                    stk.top() = to_string(atoi(stk.top().c_str()) / cur);
                }
                preSign = s[i];
                cur = 0;
            }
        }
        int ans = 0;
        while (!stk.empty()) {
            ans += atoi(stk.top().c_str()); stk.pop();
        }
        return ans;
    }
    bool isNumber(char a) {
        return '0' <= a && a <= '9';
    }
    bool isOperator(char a) {
        return a == '+' || a == '-' || a == '*' || a == '/';
    }

    /* 为啥我按照左神的计算思路写出来的就是各种错误呢？ */
    // 问题1：这种方法不能处理最后的乘除法，例如2*3，会残留在栈里面
    // 问题2：清空栈的时候减法处理错误，1-1+1会先结合后面的两个1
    // 彻底晕了，找不出来了
    int calculateMy(string s) {
        int len = s.size();
        stack<string> stk;
        int cur = 0;
        
        for (int i=0; i<len; i++) {
            if ('0' <= s[i] && s[i] <= '9') { // 是数字，进行累乘
                cur = cur * 10 + (s[i] - '0');
            } 
            if (((!('0' <= s[i] && s[i] <= '9')) && s[i] != ' ') || (i == len-1)) {
                // 先看栈顶：3+2*3+4, 当考察到3+的时候，cur=3 s[i]="+"
                if (!stk.empty() && (stk.top()=="*" || stk.top()=="/")) { // 栈顶是*或者/，需要优先运算
                    // 弹出来两个
                    string op = stk.top(); stk.pop();
                    int num = atoi(stk.top().c_str()); stk.pop();
                    // 算出来一个数，压回去
                    if (op=="*") stk.push(to_string(num * cur));
                    else if (op=="/") stk.push(to_string(num / cur));
                } else {
                    // 数字结束，并且捕获到符号
                    stk.push(to_string(cur));
                }
                stk.push(s.substr(i, 1)); // 新的操作符压回去
                cur = 0;
            }
        }
        // stk.push(to_string(cur)); // 记得对最后一个数字压栈

        // 开始清空整个栈
        while (stk.size() >=3 ) {
            int num1 = atoi(stk.top().c_str()); stk.pop();
            string op = stk.top(); stk.pop();
            int num2 = atoi(stk.top().c_str()); stk.pop();
            if (op=="+") stk.push(to_string(num1 + num2));
            else if (op=="-") stk.push(to_string(num2 - num1));
            else if (op=="*") stk.push(to_string(num2 * num1));
            else if (op=="/") stk.push(to_string(num2 / num1));
        }
        return atoi(stk.top().c_str());
    }
};