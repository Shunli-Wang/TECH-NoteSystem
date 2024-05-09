// https://leetcode.cn/problems/reverse-bits/
#include<iostream>
using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for (int i=0; i<32; i++) {
            if (((n >> i) & (uint32_t)1) != 0) { // 右移到最右侧，判断[0]位置，是1则记录
                ans |= (uint32_t) 1 << (32-i-1); // 注意位数的计算，按照高到低记录即可
            }
        }
        return ans;
    }
    // 左神给的大神实现? 
    
};
