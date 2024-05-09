// https://leetcode.cn/problems/minimum-genetic-mutation/
#include<iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;

class Solution {
public:
    /* 通过哈希表完成双向广搜 */
    bool deltaIsOne(string cur, string adj) {
        int cnt = 0;
        for (int i=0; i<cur.size(); i++) {
            if (cur[i] != adj[i]) {
                cnt++;
            }
        }
        return cnt == 1;
    }

    int minMutation(string startGene, string endGene, vector<string>& bank) {
        // 建立哈希表
        set<string> dict;
        for (string& word : bank) dict.insert(word);
        if (dict.count(endGene) == 0) return -1;

        // 需要的信息集合
        set<string> startSet, endSet, record;
        startSet.insert(startGene);
        endSet.insert(endGene);

        // 开始双向BFS
        int cnt = 0;
        while (!startSet.empty()) {
            set<string> tempSet;
            for (auto& cur : startSet) {
                // 看对方阵营中是否有相差1个的，存在一个跳跃
                for (auto& word : endSet) {
                    if (deltaIsOne(cur, word)) return cnt+1;
                }
                // 和word相邻的基因，全部考察
                for (auto& adj : dict) {
                    if (deltaIsOne(cur, adj) && record.count(adj) == 0) {
                        tempSet.insert(adj);
                        record.insert(adj);
                    }
                }
            }
            startSet = tempSet.size() < endSet.size() ? tempSet : endSet;
            endSet = tempSet.size() < endSet.size() ? endSet : tempSet;
            cnt++;
        }
        return -1;
    }
};
