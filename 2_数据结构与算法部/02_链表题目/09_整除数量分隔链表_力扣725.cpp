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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> resVec(k, NULL);

        // 统计长度
        ListNode* tmp = head;
        int len = 0;
        for (; tmp != NULL; len++) { tmp = tmp->next; }
        // 计算格子的数量
        int num[k];
        for (int i = 0; i < k; i++) { num[i] = len / k; }
        for (int j = 0; j < len % k; j++) { num[j] += 1; }

        // 创建初始节点
        ListNode* initNode = new ListNode(0);
        initNode->next = head;
        ListNode* cur = initNode;

        // 循环处理，截取num[kit]长度的链表
        for (int kit = 0; kit < k; kit++) { // ！！！这里kit++写成了k++，时间超出限制
            while (num[kit] != 0) {
                head = head->next;
                cur = cur->next; // ！！！忘记更新cur
                num[kit]--;
            }
            cur->next = NULL;
            resVec[kit] = initNode->next;

            initNode->next = head;
            cur = initNode; 
        }

        delete initNode;
        return resVec;
    }
};
