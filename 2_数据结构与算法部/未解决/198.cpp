


class Solution {
public:
    // 暴力递归改出来的动态规划
    int dfs(vector<int>& nums, int idx, bool limit, vector<int>& dpT, vector<int>& dpF) {
        if (idx == nums.size()) return 0; // 末尾状态，返回0
        // 查表
        if (dpT[idx] != -1 && dpF[idx] != -1) return !limit ? max(dpT[idx], dpF[idx]) : dpF[idx]; // 有数值，太好了，直接返回

        // 没查到，暴力找
        int res1=0, res2=0;
        if (!limit) { // 没限制
            res1 = nums[idx] + dfs(nums, idx+1, true, dpT, dpF); // idx要了，idx+1不能要了
            dpT[idx] = res1;
        }
        res2 = dfs(nums, idx+1, false, dpT, dpF); // idx没有要，继续不设限制
        dpF[idx] = res2;

        return !limit ? max(dpT[idx], dpF[idx]) : dpF[idx];
    }

    int rob(vector<int>& nums) {
        vector<int> dpT(nums.size(), -1);
        vector<int> dpF(nums.size(), -1);
        // 给了初始状态，请你返回最终结果的钱数
        int maxMoney = dfs(nums, 0, false, dpT, dpF); // 没有限制，上一家没有要
        return maxMoney;
    }
};


class Solution1 {
public:

    // 全局money写法的暴力递归
    int ans = 0;
    void dfs(vector<int>& nums, int idx, bool rob, int money) {
        if (idx == nums.size()) { // basecase, 已经分析完了整个数组
            ans = max(ans, money);
            return;
        }
        if (rob) { // 若偷了idx家，则加钱，不能偷下一家
            dfs(nums, idx+1, false, money+nums[idx]);
        } else { // 若没偷idx家，下面一家进行两种尝试
            dfs(nums, idx+1, true, money);
            dfs(nums, idx+1, false, money);
        }
    }
    int rob(vector<int>& nums) {
        dfs(nums, 0, true, 0);
        dfs(nums, 0, false, 0);
        return ans;
    }
};
