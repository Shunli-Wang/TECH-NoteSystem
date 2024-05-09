// https://leetcode.cn/problems/as-far-from-land-as-possible/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    // 移动数组
    vector<vector<int>> moves = {{0, 1},{1, 0},{0, -1},{-1, 0}};

    // 多源最短路径问题，使用BFS
    // 陆地向外扩展，只到扩到不能再扩为止，进行中途计数
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        if (n == 1 && m == 1) return -1; // 只有一个数字，直接返回

        // BFS需要使用的队列和记录表
        queue<pair<int, int>> que;
        vector<vector<int>> record(n, vector<int>(m, 0)); // 建议使用矩阵方法做记录表，比set快很多

        // BFS初始化
        int cntLand = 0, cntOcean = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (grid[i][j] == 1) { // 所有陆地位置进入队列，且进入哈希表
                    que.push({i, j});
                    record[i][j] = 1;
                    cntLand++;
                } else cntOcean++;
            }
        }
        if (cntLand == n*m || cntOcean == n*m) return -1; // 全部是海洋或者陆地

        // BFS搜索
        int ans = 0;
        while (!que.empty()) { // 标准的BFS
            int cnt = que.size();
            for (int i=0; i<cnt; i++) {
                pair<int, int> cur = que.front(); que.pop(); // 外扩当前点，找到新点(x,y)
                for (vector<int>& move : moves) {
                    int x = cur.first + move[0];
                    int y = cur.second + move[1];
                    // (x,y)不越界 && 没有出现在记录表中过
                    if (0<=x && x<n && 0<=y && y<m && record[x][y] == 0) {
                        // 扩张此点 当作陆地添加到队列中 以及记录表
                        que.push({x, y});
                        record[x][y] = 1;
                    }
                }
            }
            ans++;
        }
        return ans - 1; // 因为最开始的状态出现了一次que清空，所以最后是多计算了一次
    }
};
