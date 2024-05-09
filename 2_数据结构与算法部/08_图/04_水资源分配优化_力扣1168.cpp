// https://leetcode.cn/problems/optimize-water-distribution-in-a-village/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[2] < b[2];
    }
};

class Solution {
public:
    int MAXN = 10001;
    int* father = new int[MAXN];
    void build(int n) {
        for (int i=0; i<=n; i++) { // [0, 1, 2, 3] 0也要启用
            father[i] = i;
        }
    }
    int find(int i) {
        if (father[i] != i) {
            father[i] = find(father[i]);
        }
        return father[i];
    }
    bool unionSet(int a, int b) {
        int fa = find(a);
        int fb = find(b);
        if (fa != fb) {
            father[fa] = fb;
            return true; // 合并后执行运算
        } else return false;
    }

    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // 创建并查集
        build(n);

        // 将独立水井路线添加到边中，将井源也视为一个节点
        for (int i=0; i<wells.size(); i++) {
            pipes.push_back({0, i+1, wells[i]});
        }

        // 边从小到大排序
        sort(pipes.begin(), pipes.end(), cmp());

        int ans = 0;
        for (auto pipe : pipes) {
            if (unionSet(pipe[0], pipe[1])) { // 不在同一集合，需要合并
                ans += pipe[2];
            }
            // 如果两者已经在同一集合，不用处理，舍弃掉pipe
        }
        return ans;
    }
};
