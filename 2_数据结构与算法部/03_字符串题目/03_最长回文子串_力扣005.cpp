// https://leetcode.cn/problems/longest-palindromic-substring
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    // 标准预处理函数
    string preProcess(string s) {
        string res = "#";
        for (int i=0; i<s.size(); i++) {
            res = res + s[i] + "#";
        }  
        return res;
    }

    string longestPalindrome(string s) {
        string str = preProcess(s);
        vector<int> radArr(str.size(), 0); // 回文半径数组，存放以每一个字符开始的最大半径
        // 暴力解
        for (int i=0; i<str.size(); i++) {
            int j = 1;
            while (0 <= i-j && i+j <= str.size() && str[i-j] == str[i+j]) {
                j++;
            }
            radArr[i] = j;
        }
        // 找到最大下标
        int idx = -1;
        int maxLen = INT32_MIN;
        for (int i=0; i<str.size(); i++) {
            if (radArr[i] > maxLen) {
                maxLen = radArr[i];
                idx = i;
            }
        }
        // 复原字符串
        bool flag = false;
        string res = "";
        for (int j=idx-(maxLen-1); j<=idx+(maxLen-1); j++) { // 闭区间遍历
            if (flag) res = res + str[j]; 
            flag = !flag;
        }

        return res;

        // Manacher算法实现
        // int R = -1; // 最远回文右边界，闭区间写法，R为元素
        // int c = -1; // 最远回文右边界所对应的半径位置

        // // 逐个遍历
        // for (int i=0; i<str.size(); i++) {
        //     if (i > R) { // 暴力扩展

        //     } else { // 镜像映射边界出现的三种情况
        //         int j = 2 * c - i; // 镜像点
        //         int di = radArr[j] - 1; // 对于i来说能向右扩多少
        //         if (i + di == R) { // 压中，外扩

        //         } else if (i + di < R) { // 内部，直接出答案
        //             radArr[i] = radArr[j];
        //         }

        //         if (i == R){

        //         } else if (i < R) { // 中了[--j-c-i--]情况，可以直接使用对称结果

        //         } else if () {

        //         }
        //     }
        // }
        // return s;
    }
};
