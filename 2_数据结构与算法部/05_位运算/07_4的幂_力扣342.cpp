// https://leetcode.cn/problems/power-of-four/
#include<iostream>
using namespace std;

class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n <= 0) {return false;}
        // 只有1个0，且在特定位置上
        if (n == (n&(~n+1))) { // 使用右侧1判定是不是 2^x
            return 0x55555555 == (n | 0x55555555); // 使用0101卡特定数据
        }
        return false;
    }
};
