// https://leetcode.cn/problems/merge-k-sorted-lists
#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

    bool isAllNull(vector<ListNode*>& lists) {
        // 全都是NULL才会返回true
        bool flag = true;
        for (int i=0; i<lists.size(); i++) {
            flag &= (lists[i] == nullptr);
        }
        return flag;
    }
    /* 使用单次扫描法，一次出来一个最小值 */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 结果
        ListNode* initNode = new ListNode(0);
        ListNode* cur = initNode;
        
        // 单次扫描得到最小值位置
        int min;
        int idx = 0;
        ListNode* tmp = nullptr;

        while (!isAllNull(lists)) {
            min = INT32_MAX;
            for (int i=0; i<lists.size(); i++) {
                if (lists[i] != nullptr && lists[i]->val < min) { // 存在节点 && 刷新了最小值
                    min = lists[i]->val;
                    idx = i; // 找到了min节点
                }
            }
            tmp = lists[idx]; // 记录节点
            lists[idx] = lists[idx]->next; // 更新节点

            // 链接
            tmp->next = nullptr;
            cur->next = tmp;
            cur = cur->next;
        }
        ListNode* ans = initNode->next;
        delete initNode;
        return ans;
    }
};
