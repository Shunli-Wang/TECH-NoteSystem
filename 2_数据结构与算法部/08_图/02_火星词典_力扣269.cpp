// https://leetcode.cn/problems/alien-dictionary/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {

        // 建立字母的入度表，未出现是-1，出现过是0
        vector<int> inDegree(26, -1);
        for (string word : words) {
            for (int i=0; i<word.size(); i++) {
                inDegree[word[i] - 'a'] = 0;
            }
        }
        // 建立字母的邻接表
        vector<vector<int>> graph(26);

        // 开始两两寻找不同，并且建图
        for (int i=0; i<words.size()-1; i++) {
            string strA = words[i];
            string strB = words[i+1];
            // 开始寻找第一个不同的位置（左右同步的双指针找相同）
            int len = min(strA.size(), strB.size());
            int j=0;
            for (; j<len; j++) {
                if (strA[j] != strB[j]){ // 不相等，出现了字典序对，进行建图，并且跳出
                    graph[strA[j]-'a'].push_back(strB[j]-'a'); // strA -> strB
                    inDegree[strB[j]-'a']++;
                    break;
                }
            }
            if (j == len && strA.size() > len) return ""; // 不可能出现 abcd 在 abc前面的情况（这个特殊情况太难想了...）
        }

        // 开始拓扑排序
        queue<int> que;
        int allCharCnt = 0;
        for (int i=0; i<inDegree.size(); i++) {
            if (inDegree[i] == 0) que.push(i);
            if (inDegree[i] != -1) allCharCnt++; // 统计所有字母数量
        }

        string ans = "";
        while (!que.empty()) {
            int cur = que.front(); que.pop(); // 弹出一个0入度的字符
            ans += 'a' + cur; // 放到答案中
            for (int adj : graph[cur]) {
                inDegree[adj]--;
                if (inDegree[adj] == 0) {
                    que.push(adj);
                }
            }
        }

        return ans.size() == allCharCnt ? ans : "";
    }
};
