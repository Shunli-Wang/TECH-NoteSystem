// https://leetcode.cn/problems/container-with-most-water/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /* 左右剥洋葱，依次记录所有最优解 */
    int maxArea(vector<int>& height) {
        // 每一根杆进行思考：大于等于>=我的，离我最远的，在哪里？
        // 左右剥离的方法，逐步剥洋葱，获取每一根杆的最优解
        int len = height.size();
        int l=0, r=len-1;
        int ans=0;

        while (l < r) {
            if (height[l] <= height[r]) {
                ans = max(ans, (r-l)*height[l]);
                l++;
            } else {
                ans = max(ans, (r-l)*height[r]);
                r--;
            }
        }
        return ans;
    }
};
