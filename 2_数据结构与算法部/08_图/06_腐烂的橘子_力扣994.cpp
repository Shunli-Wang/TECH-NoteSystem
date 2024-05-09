// https://leetcode.cn/problems/rotting-oranges/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> moves = {{0,1},{1,0},{0,-1},{-1,0}};

    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // BFS必备信息
        queue<pair<int, int>> que;
        vector<vector<int>> record(n, vector<int>(m, 0)); // 0表示可达, 1表示不可达

        int rotOrangeCnt = 0; // 坏橘子数量
        int kepOrangeCnt = 0; // 好橘子数量
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (grid[i][j] == 2) {
                    que.push({i, j});
                    record[i][j] = 1; // 已经入队列的点不可达
                    rotOrangeCnt++;
                } else if (grid[i][j] == 0) { // 空单元格不可达
                    record[i][j] = 1;
                } else kepOrangeCnt++;
            }
        }

        if (rotOrangeCnt == 0 && kepOrangeCnt != 0) return -1; // 全都是好橘子，不可能腐烂
        if (kepOrangeCnt == 0) return 0; // 没有好橘子，直接返回0min

        int num = -1; // BFS一般计数初始为-1，因为初始状态需要空运行一次。
        while (!que.empty()) {
            int cnt = que.size();
            for (int i=0; i<cnt; i++) {
                pair<int, int> cur = que.front(); que.pop();
                for (auto move : moves) {
                    int x = cur.first + move[0];
                    int y = cur.second + move[1];
                    if (0<=x && x<n && 0<=y && y<m && record[x][y] == 0) { // 可以被感染
                        que.push({x, y});
                        record[x][y] = 1;
                        kepOrangeCnt--; // 每次新腐烂一个就要进行计数，最后能够让好橘子清零
                    }
                }
            }
            num++;
        }

        return kepOrangeCnt == 0 ? num : -1; // 判断是否清零
    }
};


// 经典的二维矩阵DFS问题

