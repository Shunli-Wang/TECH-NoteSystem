#include<iostream>
#include<vector>
#include<set>
using namespace std;

int minCnt = INT32_MAX;

void dfs(int i, int j, vector<vector<int>>& grid, int cnt, int tgt, set<pair<int, int>>& set) {
    if (j == tgt) { // 到达了最右侧，找到成功案例
        minCnt = min(minCnt, cnt);
    }

    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int, int>> move = {{0,1},{1,0},{0,-1},{-1,0}};

    for (auto mov : move) {
        int iNew = i + mov[0];
        int jNew = j + mov[1];
        // 不越界 && 没有传过
        if (0 <= iNew && iNew < m && 0 <= jNew && jNew < n && set.count(pair<int, int>(iNew, jNew)) == 0) {
            // 必须是1才能继续
            if (grid[iNew][jNew] == 1) {
                set.insert(pair<int, int>(iNew, jNew));
                dfs(iNew, jNew, grid, cnt+1, tgt, set);
                set.erase(pair<int, int>(iNew, jNew));
            }
        }
    }
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid;
    for (int i=0; i<m; i++) {
        vector<int> temp(n, 0);
        for (int j=0; j<n; j++) {
            cin >> temp[j];
        }
        grid.push_back(temp);
    }

    for (int i=0; i<m; i++) {
        if (grid[i][0] == 1) {
            set<pair<int, int>> set;
            set.insert(pair<int, int>(i, 0));
            dfs(i, 0, grid, 0, n-1, set);
            set.clear();
        }
    }

    if (minCnt == INT32_MAX) {
        minCnt = -1;
    }

    cout << minCnt << endl;
}


/*
https://mp.weixin.qq.com/s/ZVB6jlPf7Ixp1QCiFynvaQ

图上的BFS
进行DFS

班级组织传球活动，男女同学随机排成m行n列队伍，第一列中的任意一个男同学都可以作为传球的起点，要求最终将球传到最后一列的任意一个男同学手里，
求所有能够完成任务的传球路线中的最优路线(传球次数最少的路线)的传球次数。

4 4

1 1 1 0
1 1 1 1
0 0 1 0
0 1 1 1

*/


