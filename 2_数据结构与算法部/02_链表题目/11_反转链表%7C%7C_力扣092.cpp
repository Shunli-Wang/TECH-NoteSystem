#include<iostream>
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
    ListNode* process(ListNode* node) { // 递归反转链表
        if (node->next == NULL) { // basecase处理，返回自身节点
            return node;
        }
        ListNode* nextNode = process(node->next); // 弹栈能够逆序，所以获取下层节点
        nextNode->next = node; // 篡改自身指针，不影响之前节点
        return node; // 返回自身节点
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {

        if (left == right) { return head; }

        // 链表三连
        ListNode* initNode = new ListNode(0);
        initNode->next = head;
        ListNode* cur = initNode;

        // 剥离操作，cur前置，suc后置
        for (int i=0; i<left-1; i++) { // 找到头节点
            head = head->next;
            cur = cur->next;
        }
        ListNode* pHead = head; // 目标头

        for (int i=0; i<(right-left); i++) { // 找到尾节点
            head = head->next;
        }
        ListNode* pTail = head; // 目标尾
        ListNode* suc = head->next; // 目标尾后续

        // 递归反转链表
        pTail->next = NULL;
        pHead = process(pHead);

        // 连接链表
        cur->next = pTail;
        pHead->next = suc;

        ListNode* ans = initNode->next;
        delete initNode;
        return ans;
    }
};
