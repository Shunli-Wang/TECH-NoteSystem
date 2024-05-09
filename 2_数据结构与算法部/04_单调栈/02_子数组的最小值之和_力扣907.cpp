// 虽然标记为中等，但是其实是难题，难在单调栈的重复值处理，可以简化为不处理
// 左神052课程
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int MOD = 1000000007;
        int len = arr.size();
        long ans = 0;

        // 单调栈元素
        stack<int> stk;
        vector<int> left(len, 0), right(len, 0);

        // 1循环遍历
        for (int i=0; i<len; i++) {
            while (!stk.empty() && arr[stk.top()] >= arr[i]) {
                int index = stk.top(); stk.pop();
                left[index] = stk.empty() ? -1 : stk.top();
                right[index] = i;
                // 清算index节点时出结果（主角不是i而是index）
                ans = (
                    ans + (long) (index - left[index]) * (right[index] - index) * arr[index]
                    ) % MOD; // 神奇，-1也可以代入运算
            }
            stk.push(i);
        }

        // 2结尾清算
        while (!stk.empty()) {
            int index = stk.top(); stk.pop();
            left[index] = stk.empty() ? -1 : stk.top();
            right[index] = len; // 经典的是填-1，右侧若没有则可以填n，后续计算用到
            // 清算index节点时出结果
            ans = (
                    ans + (long) (index - left[index]) * (right[index] - index) * arr[index]
                    ) % MOD; // 神奇，-1也可以代入运算
        }
        return (int) ans;
    }
};

// 1. 直接对单调栈的左右最近min程序进行改写，变为范围内的乘积求和问题；
// 2. 等于的位置可以跳过，因为后续会完成所有的结算；
// 3. 单调栈中不允许出现两个相同值，这是最经典的用法。
// 4. 用三段单调栈模板求严格最大最小，是可以的，但是在最后可以化简

