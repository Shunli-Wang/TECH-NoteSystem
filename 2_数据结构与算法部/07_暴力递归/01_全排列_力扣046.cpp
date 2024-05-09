// https://leetcode.cn/problems/permutations/
#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:

    // 官方题解
    void process1(vector<vector<int>>& ans, vector<int>& nums, int first, int len) {
        // 可以将题目给定的的数组划分成左右两个部分，左边的表示已经填过的数，右边表示待填的数
        if (first == len) {
            ans.push_back(nums); return;
        }
        for (int i=first; i<len; i++) { // 让每个位置的数字都能来到初始位置
            swap(nums[i], nums[first]);
            process1(ans, nums, first+1, len);
            swap(nums[i], nums[first]); // 原位操作，结束之后再换回来
        }
    }

    // 没有写成功
    void process(vector<int>& nums, int len, vector<vector<int>>& ans, vector<int> cur, unordered_set<int> set) {
        if (cur.size() == len) { // basecase 到达长度直接返回
            ans.push_back(cur); return;
        }
        for (int i=0; i<len; i++) { // 每个字符都考察一遍，考察过下标放入哈希表。用过的字符不能在后续选用
            if (set.find(i)==set.end()) { // 还未添加过，已经用过了，必须选出来没有用过的才能迭代
                cur.push_back(nums[i]); // 添加字符，继续往下传
                set.insert(i); // 表格记录上下标
                process(nums, len, ans, cur, set);
                set.erase(i); // 擦掉
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;

        process1(ans, nums, 0, nums.size());

        return ans;
    }
};

