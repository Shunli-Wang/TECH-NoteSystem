// https://leetcode.cn/problems/single-number-iii
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // 从头到尾异或，得到a^b
        int ab = 0;
        for (int i : nums) {
            ab ^= i;
        }
        // 获取a和b的最低歧义位
        int loc = ab == INT32_MIN ? INT32_MIN : ab & (~ab + 1); // ab & (-ab) 与自身相反数相与，获取最右侧的1， 0000 0100
        // 根据歧义位划分阵营
        int a = 0;
        for (int i : nums) {
            if ((loc & i) == 0) { // 筛选此位置为0的所有数字 0000|0100 & 0110|0[0]00 == 0
                a ^= i;
            }
        }
        // 返回结果
        vector<int> res = {a, a^ab};
        return res;
    }
};

// 大坑啊，若有系统最小值INT32_MIN，无法通过相反数操作
// [1,1,0,-2147483648]
