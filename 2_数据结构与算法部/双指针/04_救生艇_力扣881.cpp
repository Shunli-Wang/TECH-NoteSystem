// https://leetcode.cn/problems/boats-to-save-people/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct cmp{
    bool operator()(int& a, int& b) {
        return a > b;
    }
};

class Solution {
public:
    /* 配合贪心算法使用，发货思维 */
    int numRescueBoats(vector<int>& people, int limit) {
        int len = people.size();
        sort(people.begin(), people.end(), cmp()); // 降序排列

        int ans = 0;
        int l=0, r=len-1;
        while (l < r) {
            if (people[l] + people[r] <= limit) { // 两个人可以同坐
                l++; r--; ans++;
            } else {
                l++; ans++; // 先发送重的人
            }
        }
        if (l == r) ans++; // 如果最后还剩下了一个单独的人

        return ans;
    }
};

