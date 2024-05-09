#include<iostream>
#include<vector>
#include<set>
using namespace std;

int maxVal = 0;

void dfs(int i, int j, vector<vector<int>>& grid, int cnt, bool isUp, set<pair<int, int>>& set) {
    // 可以走
    int m = grid.size();
    int n = grid[0].size();
    int cur = grid[i][j];

    // basecase: 走无可走，返回cnt
    maxVal = max(maxVal, cnt);

    vector<vector<int>> mat;
    mat.push_back(vector<int>{0, 1});
    mat.push_back(vector<int>{1, 0});
    mat.push_back(vector<int>{0, -1});
    mat.push_back(vector<int>{-1, 0});

    for (auto move : mat) { // 使用for循环进行处理，可以节省很多代码空间
        int iNew = i + move[0];
        int jNew = j + move[1];
        // 不越界而且没有考察过此点
        if (0 <= iNew && iNew < m && 0 <= jNew && jNew < n && set.count(pair<int, int>(iNew, jNew)) == 0) {
            set.insert(pair<int, int>(iNew, jNew));
            if ((isUp && cur > grid[iNew][jNew]) || ((!isUp) && cur < grid[iNew][jNew])) { // 往下走 & 往上走
                dfs(iNew, jNew, grid, cnt+1, !isUp, set);
            }
            set.erase(pair<int, int>(iNew, jNew));
        }
    }
}

int main() {
    int m, n;
    cin >> m; cin >> n;

    vector<vector<int>> grid;
    for (int i=0; i<m; i++) {
        vector<int> temp;
        for (int j=0; j<n; j++) {
            int val; cin >> val;
            temp.push_back(val);
        }
        grid.push_back(temp);
    }

    // DFS回溯
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            set<pair<int, int>> set;
            set.insert(pair<int, int>(i,j));
            dfs(i, j, grid, 0, true, set);
            dfs(i, j, grid, 0, false, set);
            set.clear();
        }
    }
    
    cout << maxVal << endl;

    return 0;
}

// 经典的DFS递归，对状态进行修改和复原
