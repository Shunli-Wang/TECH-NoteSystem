// https://leetcode.cn/problems/power-of-two/
#include<iostream>
using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) {return false;} // 考虑全部范围的数值
        int cnt = 0;
        for (int i=0; i<31; i++) {
            if (((n >> i) & 1) != 0) {
                cnt++;
            }
        }
        return cnt == 1 ? true : false; // 只含有1个1则是2的幂
    }
};
