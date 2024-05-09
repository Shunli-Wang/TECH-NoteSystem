// https://leetcode.cn/problems/find-the-duplicate-number
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    // 利用下标建图，佛洛依德判圈法
    int findDuplicate(vector<int>& nums) {
        // 寻找第一次碰面
        int slow = nums[0]; // 注意一开始是s=f，并且s走一步，f走两步，init状态一定要设定好，不然会出错
        int fast = nums[nums[0]];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        cout << slow << fast << endl;
        // 到达了碰面地方
        fast = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return fast; // 直接返回这个数字即可
    }
};

// 初始状态：
// [0]->[1]->[2]
//       s    f

// 错误初始状态！：
// [0]->[1]->[2]
//  s    f 
