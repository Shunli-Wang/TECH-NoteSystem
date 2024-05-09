// https://leetcode.cn/problems/trapping-rain-water-ii/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct cmp {
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[2] > b[2]; // 正常是小于，但是优先级队列是大于
    }  
};

class Solution {
public:
    vector<vector<int>> moves = {{0,1},{1,0},{0,-1},{-1,0}};
    int trapRainWater(vector<vector<int>>& heightMap) {
        // ———— 初始状态
        // 做好小根堆入堆工作，找到最小值，设定海平面h；
        // 拽进来所有邻居：
        //         1. 比自己高的直接进
        //         2. 比自己低的结算水滴之后再进h-arr[i]，并且修改高度为h

        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<vector<int>, vector<vector<int>>, cmp> heap;
        vector<vector<int>> table(m, vector<int>(n ,0)); // 记录表0表示可达，1表示不可达

        // 外围全部入堆
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (i == 0 || j == 0 || i == m-1 || j == n-1) {
                    heap.push({i, j, heightMap[i][j]}); table[i][j] = 1;
                } 
            }
        }

        int ans = 0;

        // 堆顶
        while (!heap.empty()) {
            // 堆顶元素，开始一轮扩展
            vector<int> cur = heap.top(); heap.pop(); 
            int level = cur[2];
            cout << level << endl;

            // 遍历每一个周围元素
            for (vector<int>& move : moves) {
                int x = cur[0] + move[0];
                int y = cur[1] + move[1];
                // 不越界并且可达情况
                if (0<=x && x<m && 0<=y && y<n && table[x][y] == 0) { 
                    if (heightMap[x][y] < level) { // 能够产生存蓄
                        ans += (level - heightMap[x][y]);
                        heap.push({x, y, level}); table[x][y] = 1; // 入堆
                    } else { // 不能产生存蓄
                        heap.push({x, y, heightMap[x][y]}); table[x][y] = 1; // 入堆
                    }
                }
            }
        }
        return ans;
    }
};