// https://leetcode.cn/problems/number-of-islands/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void inflect(vector<vector<char>>& grid, int m, int n, int M, int N) {
        grid[m][n] = '0';
        // 想清楚条件，不越界 && 是1，则进行扩散
        if (m>0 && grid[m-1][n]=='1') {inflect(grid, m-1, n, M, N);} // 若能向上扩散
        if (n>0 && grid[m][n-1]=='1') {inflect(grid, m, n-1, M, N);} // 若能向左扩散
        if (m<(M-1) && grid[m+1][n]=='1') {inflect(grid, m+1, n, M, N);} // 若能向下扩散
        if (n<(N-1) && grid[m][n+1]=='1') {inflect(grid, m, n+1, M, N);} // 若能向右扩散
    }
    int numIslands(vector<vector<char>>& grid) {
        int M = grid.size();
        int N = grid[0].size();

        int ans = 0;
        for (int m=0; m<M; m++) {
            for (int n=0; n<N; n++) {
                if (grid[m][n] == '1') {
                    ans++;
                    inflect(grid, m, n, M, N);
                }
            }
        }
        return ans;
    }
};
