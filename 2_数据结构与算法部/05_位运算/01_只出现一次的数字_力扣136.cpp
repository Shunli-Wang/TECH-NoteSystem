// https://leetcode.cn/problems/single-number/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i : nums) {
            res ^= i;
        }
        return res;
    }
};

// 题目问的是出现1次，但是其实可以推广到出现奇数次和偶数次
// 异或性质：a^a=0, a^0=a
// 若出现了奇数次必然会留下一个数字，其余偶数次全部被异或消除

