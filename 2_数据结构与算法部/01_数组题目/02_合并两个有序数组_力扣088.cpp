// https://leetcode.cn/problems/merge-sorted-array/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    // 双指针
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> ans(nums1.size(), 0);
        for (int i=0; i<nums1.size(); i++) {
            ans[i] = nums1[i];
        }
        int i=0;
        int j=0;
        while (i<m && j<n) { // 都没有到头
            if (ans[i] <= nums2[j]) {
                nums1[i+j] = ans[i]; i++;
            } else {
                nums1[i+j] = nums2[j]; j++;
            }
        }
        if (i==m) { // 左到了头，搞右
            while (j<n) {
                nums1[i+j] = nums2[j]; j++;
            }
        }
        if (j==n) { // 右到了头，搞左
            while (i<m) {
                nums1[i+j] = ans[i]; i++;
            }
        }
        return;
    }
};