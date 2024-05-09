// https://leetcode.cn/problems/01-matrix
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> moves = {{0, 1},{1, 0},{0, -1},{-1, 0}};

    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> ans(mat);

        // 经典BFS
        queue<pair<int, int>> que;
        vector<vector<int>> record(n, vector<int>(m, 0)); // 可达为0，不可达为1

        // 遍历确定初始状态
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (mat[i][j] == 0) {
                    que.push(pair<int,int>(i, j));
                    record[i][j] = 1;
                }
            }
        }

        int num = 0;
        while(!que.empty()) {
            num++; // 一开始就先加1，填充ans数组。只要感染新的数值，就记录步骤数量。
            int cnt = que.size();
            for (int i=0; i<cnt; i++) {
                pair<int, int> cur = que.front(); que.pop();
                for (auto& move : moves) {
                    int x = cur.first + move[0];
                    int y = cur.second + move[1];
                    if (0<=x && x<n && 0<=y && y<m && record[x][y] == 0) {
                        que.push(pair<int,int>(x, y));
                        record[x][y] = 1;
                        ans[x][y] = num;
                    }
                }
            }
        }

        return ans;
    }
};

// for (auto& move : moves) 如果没有&就是值传递，会非常慢
