// https://leetcode.cn/problems/word-ladder/
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
using namespace std;

class Solution {
public:

    /* 翻译的左神java版本的双向BFS */
    int ladderLength_Zuo(string beginWord, string endWord, vector<string>& wordList) {
        set<string> dict;
        for (string& word : wordList) dict.insert(word);
        if (dict.count(endWord) == 0) return 0; // 居然没有这个单词

        set<string> startSet, endSet, visit;
        startSet.insert(beginWord);
        endSet.insert(endWord);

        for (int len=2; !startSet.empty(); len++) { // 起始的步骤数量为2
            set<string> nextSet;
            for (auto cur : startSet) { // 所有队列中的单词
                for (int i=0; i<cur.size(); i++) { // 滑过每一个位置的字母
                    string temp = cur;
                    for (char c='a'; c<='z'; c++) {
                        if (temp[i] == c) continue;
                        temp[i] = c;
                        if (endSet.count(temp) != 0) return len; // 找到目标
                        if (dict.count(temp) !=0 && visit.count(temp) == 0) { // 单词表中有这个变种 && 没有访问过
                            nextSet.insert(temp);
                            visit.insert(temp);
                        }
                    }
                }
            }
            startSet = nextSet.size() < endSet.size() ? nextSet : endSet;
            endSet = nextSet.size() < endSet.size() ? endSet : nextSet;
        }
        return 0;
    }

    /* 单向BFS，时间没通过 */
    bool deltaIsOne(string a, string b) {
        int len = a.size();
        for (int i=0; i<len; i++) {
            for (int j='a'; j<='z'; j++) {
                string temp = a;
                if (j == temp[i]) continue; // 和原来字符重复
                temp[i] = j;
                if (temp == b) return true;
            }
        }
        return false;
    }
    int ladderLengthSingle(string beginWord, string endWord, vector<string>& wordList) {
        // 初始化一个哈希表当邻接矩阵使用
        map<string, vector<string>> graph;
        for (string& word : wordList) {
            graph[word] = {};
        }
        if (graph.count(endWord) == 0) return 0; // 没有结束单词，一定无法转换
        // 先把开始词加进去
        wordList.push_back(beginWord);
        graph[beginWord] = {};
        // 最后的总大小
        int len = wordList.size();

        // 创建Graph
        for (int i=0; i<len; i++) {
            for (int j=0; j<len; j++) {
                if (i != j) {
                    // 如果只相差一个字母，放入邻接表中
                    if (deltaIsOne(wordList[i], wordList[j])) {
                        graph[wordList[i]].push_back(wordList[j]); // 全循环所以自动构建双边
                        // graph[wordList[j]].push_back(wordList[i]);
                    }
                }
            }
        }

        // 开始BFS
        set<string> que;
        set<string> record;
        que.insert(beginWord);
        record.insert(beginWord);

        int ans = 1;

        while (!que.empty()) {
            set<string> temp(que); // 拍摄快照
            que.clear();
            for (auto& cur : temp) { // 遍历当前小的集合
                // 居然走通了
                if (cur == endWord) return ans; 
                // 没走通，更新下smlQue
                for (string& adj : graph[cur]) { 
                    if (record.count(adj) == 0) { // 没走过这条路
                        que.insert(adj);
                        record.insert(adj);
                    }
                }
            }
            ans++;
        }

        return 0;
    }

    /* 双向BFS，没有实现好 */ 
    /* 写不对，是真的能把人的脾气调没 */
    /* 还是不对，为啥自己建图总是错误呢 */
    /* 双向广搜，写对了但是时间过不去 */
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 初始化一个哈希表当邻接矩阵使用
        map<string, vector<string>> graph;
        for (string& word : wordList) graph[word] = {};
        if (graph.count(endWord) == 0) return 0; // 没有结束单词，一定无法转换

        // 如有需要，先把开始词加进去
        if (graph.count(beginWord) == 0) wordList.push_back(beginWord);
        graph[beginWord] = {};

        // 最后的总大小
        int len = wordList.size();

        // 创建Graph
        for (int i=0; i<len; i++) {
            for (int j=0; j<len; j++) {
                if (i != j) {
                    // 如果只相差一个字母，放入邻接表中
                    if (deltaIsOne(wordList[i], wordList[j])) {
                        graph[wordList[i]].push_back(wordList[j]); // 全循环所以自动构建双边
                        // graph[wordList[j]].push_back(wordList[i]);
                    }
                }
            }
        }

        // 开始BFS
        set<string> que1, que2, record;
        que1.insert(beginWord); que2.insert(endWord);
        record.insert(beginWord); record.insert(endWord);

        set<string> smlQue = que1;
        set<string> bigQue = que2;

        for (int cnt=2; !smlQue.empty(); cnt++) { // 起始的步骤数量为2
            set<string> nextSet;
            for (auto cur : smlQue) { // 所有队列中的单词
                // cout << cur << endl;
                // 居然走通了
                // ！！！两个阵营还有一步跨越，错误就在这里！对cur进行变字母，变成了就算。但是都被record记录好了，没办法跳跃。
                // if (bigQue.count(cur) != 0) return cnt; // 
                for (auto& word : bigQue) {
                    for (string& wordAdj : graph[word]) {
                        if (cur == wordAdj) return cnt;
                    }
                }
                // 没走通，更新que
                for (string& adj : graph[cur]) { 
                    if (record.count(adj) == 0) { // 没走过这条路
                        nextSet.insert(adj);
                        record.insert(adj);
                    }
                }
            }
            smlQue = nextSet.size() < bigQue.size() ? nextSet : bigQue;
            bigQue = nextSet.size() < bigQue.size() ? bigQue : nextSet;

        }
        return 0;
    }
};

// 1. 自己的实现：试图用经典的graph邻接表配合record表完成
// 2. 实现问题：双向广搜碰面的时候是需要一次变化的，如果使用record进行双向记录，则无法进行见面的匹配跳跃，所以这样写很麻烦。

// 左神实现：通过临时变化的方式从逻辑上替代graph邻接表。只能说666了。
