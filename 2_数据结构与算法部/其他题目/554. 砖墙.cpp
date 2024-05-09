#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
    // 逐个元素求解导致超时
    int leastBricks(vector<vector<int>>& wall) {
        int N = 0; // 总长度
        for (int i=0; i < wall[0].size(); i++) {
            N += wall[0][i];
        }

        int vecNum = wall.size(); // 容器数量

        // 遍历统计
        int minRes = vecNum;
        int crosCnt;
        for (int n=0; n<N-1; n++) { // 横跨N-1次中缝
            crosCnt = 0;
            for (int v=0; v < vecNum; v++) {
                // 每一层的首个元素递减1
                wall[v][0]--;
                if (wall[v][0] == 0) { // 若为0，则不计数，且清除
                    wall[v].erase(wall[v].begin());
                } else { // 若不为0，计数
                    crosCnt++;
                }
            }
            minRes = min(minRes, crosCnt);
        }
        return minRes;
    }

    // 转化思想，反向求解
    int leastBricks_(vector<vector<int>>& wall) {
        int N = wall.size(); // 有n层
        unordered_map<int, int> map; // 记录第key个位置的空当数量value，这个使用非常巧妙

        int sum = 0;
        for (int i=0; i<N; i++) { // 遍历n个层
            for (int cur : wall[i]) {
                sum += cur;
                map[sum]++; // 创建后自动置0，后加一
            }
            map.erase(sum); // 删除最后一个元素
            sum=0;
        }

        int ans = N; // 遍历哈希表，找到最小数值
        for (auto kv : map) {
            ans = min(ans, N - kv.second);
        }
        return ans;
    }
};
