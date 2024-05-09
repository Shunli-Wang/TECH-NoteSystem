// 143. 重排链表
#include<iostream>
#include<stack>
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
    void reorderList(ListNode* head) {
        if (head == NULL || head->next == NULL) {return ;}
        stack<ListNode*> stk;

        ListNode* initNode = new ListNode(0);
        initNode->next = head;
        ListNode* cur = initNode;

        // 压栈 统计个数
        ListNode* tmp = head;
        int len = 0;
        while (tmp != NULL) { stk.push(tmp); len++; }

        // 根据链表节点个数判断停止
        int cnt = 0;
        while (cnt >= len) {
            // 包括一个正序节点
            head = head->next;
            cur = cur->next;
            // 包括一个逆序节点
            cur->next = stk.top(); stk.pop();
            cur = cur->next; // cur指向栈出节点
            cur->next = head;
            cnt += 2;
        }
        head->next = NULL;
        head = initNode->next;
    }
};

