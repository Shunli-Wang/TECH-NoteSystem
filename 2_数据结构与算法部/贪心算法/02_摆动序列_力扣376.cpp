// https://leetcode.cn/problems/wiggle-subsequence
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return 1;

        int ans = 0;
    
        // 1. 将序列撸成不带相邻重复数值的
        vector<int> arr; // 存放不带有重复值的序列
        int pas = INT32_MAX;
        for (int i=0; i<nums.size(); i++) {
            if (pas != nums[i]) {
                arr.push_back(nums[i]);
                pas = nums[i];
            } else {
                ans++; // 删除的相同字符
            }
        }

        // 2. 一旦发现上坡或下坡，进行计数
        if (arr.size() >= 3) {
            for (int i=0,j=1,k=2; k<arr.size(); i++,j++,k++) {
                if ((arr[i] < arr[j] && arr[j] < arr[k]) || (arr[i] > arr[j] && arr[j] > arr[k])) {
                    ans++;
                }
            }
        }

        return nums.size() - ans; // 剩下有多少个字符
    }
};

// 方法比较鸡贼，但是还是过了

