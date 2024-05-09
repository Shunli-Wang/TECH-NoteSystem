// https://leetcode.cn/problems/multiply-strings/
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    // 基元函数，一个字母乘以一个字符串
    string multiplyStrChar(string str, char ch, int radix) {
        if (ch == '0') return "";
        // 收集运算结果
        stack<char> stk;
        // 先把所有的基数填好
        for (int i=0; i<radix; i++) stk.push('0');
        // 开始进行乘法模拟
        int plus = 0;
        for (int i=0; i<str.size(); i++) { // 逆序啊这里！
            int temp = (str[str.size()-1-i] - '0') * (ch - '0') + plus;
            plus = temp / 10;
            temp = temp % 10;
            stk.push(temp + '0');
        }
        if (plus != 0) stk.push(plus + '0');
        // 吐出来字符串
        string res = "";
        while (!stk.empty()) {
            res += stk.top(); stk.pop();
        }
        return res;
    }

    string addStr(vector<string>& strArr) {
        stack<char> stk;

        // 统计最长的字符长度
        int maxLen = 0;
        for (int i=0; i<strArr.size(); i++){
            if (maxLen < strArr[i].size()) maxLen = strArr[i].size();
        } 

        // 统揽全局做加法
        int plus = 0;
        for (int i=0; i<maxLen ;i++) { // 确定每一个位，i=0指向每一个字符串的最右侧
            int temp = plus;
            for (auto& str : strArr){
                int strLen = str.size();
                if (i >= strLen) continue;
                temp += str[strLen-1-i] - '0';
            }
            plus = temp / 10;
            temp = temp % 10;
            stk.push(temp + '0');
        }
        if (plus != 0) stk.push(plus + '0');

        // 吐出来字符串
        string res = "";
        while (!stk.empty()) {
            res += stk.top(); stk.pop();
        }
        return res;
    }

    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";

        // 使用算子乘好
        int lenNum2 = num2.size();
        vector<string> strArr;
        for (int i=0; i<lenNum2; i++) {
            string cur = multiplyStrChar(num1, num2[lenNum2-1-i], i);
            cout << cur << endl;
            strArr.push_back(cur);
        }

        // 再把所有数值加起来
        string result = addStr(strArr);
        return result;
    }
};

