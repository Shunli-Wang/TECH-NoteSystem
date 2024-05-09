// https://leetcode.cn/problems/assign-cookies/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {

        // 排序，准备进行贪心
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int n = g.size();
        int m = s.size();

        int i = 0, j = 0;
        int ans = 0;

        // 双指针滑一遍
        while (i < n && j < m) {
            if (g[i] <= s[j]) {
                ans++; i++; j++;
            } else {
                j++;
            }
        }
        return ans;
    }
};

