#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    // 单调栈最优解
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int len = temperatures.size();
        stack<int> stk;
        vector<int> res(len, -1);
        // 1阶段遍历
        for (int i=0; i<len; i++) {
            while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) { // 取消=触发的弹出条件，正常压栈
                int index = stk.top(); stk.pop();
                res[index] = i; // i导致index弹出，记录右侧数值
            }
            stk.push(i);
        }
        // 2阶段清算
        while (!stk.empty()) {
            int index = stk.top(); stk.pop();
            res[index] = index; // 一定都是-1，右侧没有找到临近max数值。但是在这里方便输出，后续减法所以写入index
        }
        // 下标转化数值
        for (int i=0; i<len; i++) {
            res[i] = res[i] - i;
        }
        return res;
    }


    // 暴力解会超时
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result;
        int maxTemp = 0;
        for (int i=0; i<temperatures.size(); i++) {
            result.push_back(0); // 默认没有找到
            
            for (int j=i+1; j < temperatures.size(); j++) {
                if (temperatures[j] > temperatures[i]) { // 一旦找到右侧更大的，直接停止
                    result[i] = j-i;
                    break;
                }
            }
        }
        return result;
    }
};

