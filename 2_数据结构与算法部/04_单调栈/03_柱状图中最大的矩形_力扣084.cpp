// 大名鼎鼎的直方图最大矩形问题，单调栈直接秒了
#include<iostream>
#include<vector>
#include<stack>
#include<math>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // 单调栈：最近小min
        int len = heights.size();
        stack<int> stk;
        vector<int> left(len, 0), right(len, 0);
        // 最大矩形面积
        int ans = 0;
        // 1循环遍历
        for (int i=0; i<len; i++) {
            while (!stk.empty() && heights[stk.top()] >= heights[i]) { // 严格单调栈，会出现早期相等值被尽早结算，但是后续答案会覆盖之前的不全答案
                int idx = stk.top(); stk.pop();
                left[idx] = stk.empty() ? -1 : stk.top();
                right[idx] = i;
                ans = max(ans, (right[idx]-left[idx]-1)*heights[idx]);
            }
            stk.push(i);
        }
        // 2栈内清算
        while (!stk.empty()) {
            int idx = stk.top(); stk.pop();
            left[idx] = stk.empty() ? -1 : stk.top();
            right[idx] = len;
            ans = max(ans, (right[idx]-left[idx]-1)*heights[idx]);
        }
    return ans;
    }

    int largestRectangleArea_neat(vector<int>& heights) {
        int ans = 0; // 最大矩形面积
        int len = heights.size();
        stack<int> stk;
        vector<int> left(len, 0); // 不需要right参与
        // 1循环遍历
        for (int i=0; i<len; i++) {
            while (!stk.empty() && heights[stk.top()] >= heights[i]) {
                int idx = stk.top(); stk.pop();
                left[idx] = stk.empty() ? -1 : stk.top();
                ans = max(ans, (i-left[idx]-1)*heights[idx]);
            }
            stk.push(i);
        }
        // 2栈内清算
        while (!stk.empty()) {
            int idx = stk.top(); stk.pop();
            left[idx] = stk.empty() ? -1 : stk.top();
            ans = max(ans, (len-left[idx]-1)*heights[idx]);
        }
    return ans;
    }
};

// 转化为一个左右两侧双向扩杆的问题，杆不允许缩小，所以就是求两侧最近较小值
// 最好在经典的严格单调栈上面做分析，==情况直接弹栈，尽早结算。
// 特殊下标处理：左填-1，右侧填len和-1要具体讨论，看题目求什么
// 特殊下标处理：本质上默认arr[-1]=-00; arr[len]=-00
