// https://leetcode.cn/problems/trapping-rain-water/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /* 做题方法：自己好好画图，直到把画明白，思路自然就出来了 */

    /* 自己实现的双指针 */
    int trapMy(vector<int>& height) {
        // 若推高max，一定不会存储雨水
        // 左右两堵墙，虚实结合左右交替完成
        if (height.size() <= 2) return 0; // 两个还接什么水

        int len = height.size();

        // 确定初始条件
        int maxLeft = INT32_MIN;
        int maxRight = INT32_MIN;
        int l = 0;
        int r = len-1;

        int ans = 0;

        while (l <= r) { // 还没有结算完成的话
            // 左边能推高max吗? 如果能，肯定存不住水
            if (height[l] > maxLeft) {
                maxLeft = height[l++]; continue; // 防止l=r的情况发生，每次只运行一个++
            } else if (maxLeft <= maxRight) { // 右侧的大值让左侧的数值成为有效限制
                ans += maxLeft - height[l++]; continue;
            } 
            // 右边能推高max吗?如果能，肯定存不住水
            if (height[r] > maxRight) {
                maxRight = height[r--];
            } else if (maxLeft >= maxRight) { // 左侧的最大值让右侧的数值成为有效限制
               ans += maxRight - height[r--];
            }
        }

        return ans;
    }

    /* 单点分析法（左神提供） */
    // 1. 单独i视角：对于任何一个位置i，求出[左侧全局maxLeft]和[右侧全局maxRight]，两个求min，在减去h[i]就是能存的水量
    //     min(maxLeft, maxRight) - h[i]
    // 2. 视角特例：对于中间的独高数值，以上公式要和0求max，防止负数出现。
    //     max( min(maxLeft, maxRight) - h[i], 0 ) 
    // 3. 问题转化为：如何求出每一个位置的左侧全局max和右侧全局max预处理数组：
    //     [--maxLeft--]i[--maxRight--]
    // 4. 有了预处理数组，可以从头到尾逐个计算
    int trap(vector<int>& height) {
        int len = height.size();

        // 撸一遍数组，找出每个位置闭区间左右的max，创建辅助数组
        vector<int> leftMaxArr(len, 0);
        vector<int> rightMaxArr(len, 0);
        int a=INT32_MIN, b=INT32_MIN;
        for (int i=0; i<len; i++) {
            int j = len - 1 - i;
            if (height[i] > a) a = height[i];
            leftMaxArr[i] = a;
            if (height[j] > b) b = height[j];
            rightMaxArr[j] = b;
        }

        // 对每个位置，使用公式计算
        int ans=0;
        for (int i=1; i<len-1; i++) { // 初始和末尾一定都无法接住雨水，所以跳过，防止越界
            int leftMax = leftMaxArr[i-1];
            int rightMax = rightMaxArr[i+1];
            ans += max(min(leftMax, rightMax) - height[i], 0); // 每个位置的结果都加上去
        }
        return ans;
    }

    /* 双指针简化版本（基于单点分析优化出来的） */
    int trap(vector<int>& height) {
        int len = height.size();
        int l = 1, r = len-2;
        int maxLeft = height[0], maxRight = height[len-1];
        int ans = 0;
        while (l <= r) {
            if (maxLeft <= maxRight) { // 左边的成为了瓶颈，结算左边
                ans += max(0, maxLeft - height[l]);
                maxLeft = max(maxLeft, height[l++]);
            } else { // 右边的成为了瓶颈，结算右边
                ans += max(0, maxRight - height[r]);
                maxRight = max(maxRight, height[r--]);
            }
        }
        return ans;
    }
};
