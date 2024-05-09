// https://leetcode.cn/problems/course-schedule-ii
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

        // 创建图 & 统计各个点的入度
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);
        for (auto pre : prerequisites) { // ！！！这里是遍历边的数量啊，不是节点！不要想当然直接用i遍历
            int a = pre[0]; // 邻接点
            int b = pre[1]; // 主点
            graph[b].push_back(a); // 给的是[a,b] 其实是a<-b 
            inDegree[a]++;
        }

        // 创建队列，找到所有入度为0的点入队列
        queue<int> que;
        for (int i=0; i<numCourses; i++) {
            if (inDegree[i] == 0) {
                que.push(i);
            }
        }

        // 出队列，出一个点则进行影响擦除
        vector<int> ans;
        while (!que.empty()) {
            int cur = que.front(); que.pop(); // cur的入度一定为0
            ans.push_back(cur); // 出队列就记录
            for (int adj : graph[cur]) { // 找到所有邻居，擦除影响
                inDegree[adj]--;
                if (inDegree[adj] == 0) {
                    que.push(adj);
                }
            }
        }

        // 数量判断
        if (ans.size() != numCourses) {
            ans.clear();
        }

        return ans;
    }
};

// 输入的格式：1
//            1 2
//            2 3
int main() {
    int n; cin >> n;
    vector<vector<int>> edges;
    int a, b;
    while (cin >> a >> b) {
        edges.push_back({a, b});
    }

    return 0;
}
