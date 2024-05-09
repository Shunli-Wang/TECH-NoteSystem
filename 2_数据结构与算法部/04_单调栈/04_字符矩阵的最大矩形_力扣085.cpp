#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    int getMonoStack(vector<int>& arr) {
        // 基于84直方图统计题目
        int len = arr.size();
        stack<int> stk;
        vector<int> left(len, 0); // 化简去掉了right数组
        int ans = 0;

        for (int i=0; i<len; i++) {
            while (!stk.empty() && arr[stk.top()] >= arr[i]) {
                int idx = stk.top(); stk.pop();
                left[idx] = stk.empty() ? -1 : stk.top();
                ans = max(ans, (i-left[idx]-1)*arr[idx]);
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            int idx = stk.top(); stk.pop();
            left[idx] = stk.empty() ? -1 : stk.top();
            ans = max(ans, (len-left[idx]-1)*arr[idx]);
        }
        return ans;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int len = matrix[0].size(); // 宽度
        vector<int> rec(len, 0); // 存放压缩数组信息
        int ans = 0;

        for (vector<char> arr : matrix) { // 遍历每行
            for (int i=0; i<len; i++) {
                // 压缩之前所有行，得到当前直方图
                if (arr[i] == '0') {rec[i] = 0;} 
                else {rec[i] += 1;}
            }
            // 得到rec直方图数组，执行单调栈统计最大面积
            ans = max(ans, getMonoStack(rec));
        }
        return ans;
    }
};
