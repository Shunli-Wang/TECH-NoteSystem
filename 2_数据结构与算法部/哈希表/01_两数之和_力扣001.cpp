// https://leetcode.cn/problems/two-sum/
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    // 暴力枚举
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> temp;
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    temp = {i, j};
                    return temp;
                }
            }
        }
        return temp;
    }

    // 哈希表O(1): 
    // 不容易想到，借用了哈希表查询是O(1)的便利，依次记录每个数字的需求
    // nums[0]=2时：想找7，添加(2, 0)的记录；
    // nums[2]=7时，想找2，直接检索到(2, 0)的记录；
    vector<int> twoSumHash(vector<int>& nums, int target) {
        unordered_map<int, int> hashTable;
        // [2,11,7,15] t=9 
        for (int i=0; i<nums.size(); i++) {
            auto dest = hashTable.find(target - nums[i]); // i=0, 想找到9-2=7, 
            if (dest != hashTable.end()) { // 找到了map[7]=0的记录
                return {dest->second, i}; // 返回{0, 2}答案
            }
            hashTable[nums[i]] = i; // 添加map[2]=0的记录,下次检索到7就知道这是0所需要的
            // hashTable.insert(pair<int, int>(nums[i], i)); 
            // hashTable.insert({nums[i], i});
        }
        return {};
    }
};