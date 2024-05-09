// https://leetcode.cn/problems/3sum/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int len = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;

        for (int i=0; i<len; i++) {
            if (i > 0 && nums[i] == nums[i-1]) { // 筛选出不重复的数值i
                continue;
            }
            int k = len-1; // 数组最右侧指针k
            int delta = -nums[i];

            // 寻找这个j
            for (int j=i+1; j<len; j++) {
                if (j > i+1 && nums[j] == nums[j-1]) { // 初始状态重复也不能跳过[-1,-1,2]情况
                    continue;
                }
                while (j < k && nums[j] + nums[k] > delta) { // j在k左 && jk数值和大于目标值，才有k右移必要，重复直到<=情况
                    k--; // 构造上界
                }
                // 到此已经找到了可能出现的解边界(i,j,k)，前两个肯定不重合，j和k可能会重合
                if (j == k) { break; } // 筛选重合情况
                if (nums[j] + nums[k] == delta) { // 找到最后的解
                    ans.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
        return ans;
    }
};

// 核心思想：三指针，ij不重叠自身不重复，遍历k寻找上界。极其巧妙。

// 整体思想：
// 1. i和j指针都是从左到右，自己不和自己重复，双层循环配合if空跳；
// 2. 每次固定了i和j指针后，设定一个-nums[i]参考值；默认k指向nums[n-1]，构造一个nums[j]+nums[k]的上界
// 3. 如果nums[j]+nums[k]上界大于-nums[i]，则不断缩小k，直到nums[j]+nums[k] <= -nums[i]时停止
// 4. 到此筛选出一个可能答案，判断jk是否重合，最终判断是否相等，相等则存储。