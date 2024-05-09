#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int cnt[32]; // 非全局变量，需要显式对数组进行初始化
        for (int i=0; i<32; i++) { cnt[i] = 0; }
        // vector<int> cnt(32, 0);
        for (int num : nums) {
            for (int i=0; i<32; i++) {
                if ((num & (1 << i)) != 0) {
                    cnt[i]++;
                }
            }
        }
        int ans = 0;
        for (int i=0; i<32; i++) {
            if (cnt[i] % 3 == 1){ // 到达此位置
                ans |= (1 << i);
            }
        }
        return ans;
    }
};

// 使用位统计的方法处理1次和3次情况，m%k
