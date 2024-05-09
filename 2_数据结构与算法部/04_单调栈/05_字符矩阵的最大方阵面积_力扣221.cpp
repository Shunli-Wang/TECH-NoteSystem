#include<iostream>
#include<vector>
#include<stack>
#include<math>
using namespace std;

class Solution {
public:
    int getMaxWidth(vector<int>& rec) { // 经典单调栈（临近最小值）还是要写熟
        // 临近值：最近的min
        int len = rec.size();
        vector<int> left(len, 0), right(len, 0);
        stack<int> stk;
        int ans = 0;

        for (int i=0; i<len; i++) {
            while (!stk.empty() && rec[stk.top()] >= rec[i]) {
                int idx = stk.top(); stk.pop();
                left[idx] = stk.empty() ? -1 : stk.top();
                right[idx] = i; // 可化简
                ans = max(ans, min(right[idx]-left[idx]-1, rec[idx]));
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            int idx = stk.top(); stk.pop();
            left[idx] = stk.empty() ? -1 : stk.top();
            right[idx] = len; // 可化简
            ans = max(ans, min(right[idx]-left[idx]-1, rec[idx]));
        }
        return ans;
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        // 1.压缩数组转化为直方图问题
        // 2.使用单调栈得到left和right数组，找到临近值：最近的比自己小的，确定扩张边界

        int len = matrix[0].size(); // 宽度
        vector<int> rec(len, 0);
        int ans = 0;

        for (vector<char> row : matrix) {
            for (int i=0; i<len; i++) { // 压缩数组为直方图
                if (row[i] == '0') {rec[i] = 0; } 
                else {rec[i] += 1; }
            }
            ans = max(ans, getMaxWidth(rec));
        }
        return ans*ans; 
    }
};

// 返回的时候注意是面积，不是宽度，所以需要平方

