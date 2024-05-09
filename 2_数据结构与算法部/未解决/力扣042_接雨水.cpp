#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    // 问题：使用经典单调栈只能找到[左右]-[最近]-[比自己大]的值位置，本质上是一种局部信息
    // 接雨水题目在遍历i位置时其实需要左右的全局max值，经典单调栈使用受限。
    // 放着后面双指针做吧

    int trap(vector<int>& height) {
        // 左右两侧，最近，比自身大的数值
        int len = height.size();
        stack<int> stk;
        vector<int> left(len, 0), right(len, 0);
        // 1阶段遍历
        for (int i=0; i<len; i++) {
            while (!stk.empty() && height[stk.top()] >= height[i]) { // 若等于，则也尽早出栈结算，配合清算阶段使用
                int index = stk.top(); stk.pop(); 
                left[index] = stk.empty() ? -1 : stk.top();
                right[index] = i;
            }
            stk.push(i);
        }
        // 2阶段清算
        while (!stk.empty()) {
            int index = stk.top(); stk.pop(); 
            left[index] = stk.empty() ? -1 : stk.top();
            right[index] = -1;
        }
        // 3修正阶段
        for (int i=len-1; i>=0; i--) {
            if (right[i] != -1 && height[i] == height[right[i]]) {
                right[i] = right[right[i]];
            }
        }

        // 回顾整个单调栈结果
        int ans = 0;
        for (int i=0; i<len; i++) {
            if (left[i] == -1 || right[i] == -1) { // 不会驻留水滴
                continue;
            } else { // 生成累计驻留水滴
                ans += min(height[left[i]], height[right[i]]) - height[i];
            }
        }
        return ans;
    }
};

