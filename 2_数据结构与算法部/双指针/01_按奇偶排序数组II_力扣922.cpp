// https://leetcode.cn/problems/sort-array-by-parity-ii/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /* 左神解法：双指针，锁定末尾进行发货 */
    vector<int> sortArrayByParityII_(vector<int>& nums) {
        int len = nums.size();
        for (int i=0, j=1; i<len && j<len; ) {
            if (nums[len-1] % 2 == 0) { // 偶数位，去找i
                swap(nums[len-1], nums[i]);
                i += 2;
            } else { // 奇数位，去找j
                swap(nums[len-1], nums[j]);
                j += 2;
            }
        }
        return nums;
    }

    /* 额外空间法，遍历数组 */
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int len = nums.size();
        vector<int> help(len, 0);

        int i=0, j=1;
        for (int& num : nums) {
            if (num %2 == 0) {
                help[i] = num; 
                i += 2;
            } else {
                help[j] = num; 
                j += 2;
            }
        }
        return help;
    }
};
