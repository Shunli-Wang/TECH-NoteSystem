// https://leetcode.cn/problems/missing-number/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int a = 0;
        int b = 0;
        for (int i=0; i<nums.size(); i++) {
            a ^= nums[i]; // 从头异或到尾部，获取部分值的异或和a=(013)
            b ^= i; // 通过下标求异或和b=(012)
        }
        b ^= nums.size(); // b=(0123)
        return a ^ b; // 异或性质，群体异或a^b=(013)^(0123)=2
    }
};

// [0,1,3] 为例子
