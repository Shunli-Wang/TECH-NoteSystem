// https://leetcode.cn/problems/maximum-subarray/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    // 本质还是在打表，但是因为不用记录所以简化为for循环
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0];
        int preMax = 0; // 初始状态是max(x+0, x)不会出错

        for (int x : nums) {
            int curMax = max(preMax+x, x); // 假设已经获取到了上一轮的max，称为preMax，可以计算
            ans = max(ans, curMax); // 获取当前轮最大curMax，放到总记录中
            preMax = curMax; // 为下一轮做准备
        }

        return ans;
    }

    // 打表超时O(N^2)
    int maxSubArrayTable(vector<int>& nums) {
        int len = nums.size();

        // 创建dp表，打表
        int** table = new int*[len];
        for (int i=0; i<len; i++) {
            table[i] = new int[len];
            for (int j=0; j<len; j++) {
                table[i][j] = 0;
                if (i == j) {
                    table[i][j] = nums[i]; // 填充对角线
                }
            }
        }
        int ans = INT32_MIN;
        for (int i=0; i<len; i++) {
            ans = max(ans, table[i][i]);
            for (int j=i+1; j<len; j++) {
                table[i][j] = table[i][j-1] + nums[j];
                ans = max(ans, table[i][j]);
            }
        }
        return ans;
    }
};


/*
// 时间复杂度失败
class Solution {
private:
    
public:
    // 想利用分治法但是发现没有算完
    int getSum(vector<int>& nums, int i, int j, int** sumMax, bool** sumFlag) {
        if (i == j) { 
            sumMax[i][j] = nums[i];
            sumFlag[i][j] = true;
            return nums[i]; 
        }
        int mid = j-1;
        int leftSum = 0;
        int rightSum = 0;

        if (sumFlag[i][mid]) { // 若含有则直接用
            leftSum = sumMax[i][mid];
        } else {
            leftSum = getSum(nums, i, mid, sumMax, sumFlag); // 若不含有算了再添加
            sumMax[i][mid] = leftSum;
            sumFlag[i][mid] = true;
        }

        if (sumFlag[mid+1][j]) { // 若含有则直接用
            rightSum = sumMax[mid+1][j];
        } else {
            rightSum = getSum(nums, mid+1, j, sumMax, sumFlag); // 若不含有算了再添加
            sumMax[mid+1][j] = rightSum;
            sumFlag[mid+1][j] = true;
        }
        return leftSum + rightSum;
    }

    int maxSubArray(vector<int>& nums) {
        int** sumMax = new int*[nums.size()];
        bool** sumFlag = new bool*[nums.size()];
        for (int i=0; i<nums.size(); i++) {
            sumMax[i] = new int[nums.size()];
            sumFlag[i] = new bool[nums.size()];
            for (int j=0; j<nums.size(); j++) {
                sumMax[i][j] = 0;
                sumFlag[i][j] = false;
            }
        }
        // int allSum = getSum(nums, 0, nums.size()-1, sumMax, sumFlag); // 确保能算完
        int ans = INT_MIN;
        for (int i=0; i<nums.size(); i++) {
            for (int j=i; j<nums.size(); j++) {
                int allSum = getSum(nums, i, j, sumMax, sumFlag);
                ans = max(ans, allSum);
            }
        }
        return ans;
    }
};
*/
