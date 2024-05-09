/* 思路断了，后面再练习 */

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

    void reversePart(ListNode* head, ListNode* tail) { // 从head到tail完成反转，注意tail.next可能非空，需要智能判断


    }


    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == NULL || head->next == NULL || left == right) {return head;}

        ListNode* initNode = new ListNode(0);
        initNode->next = head;
        ListNode* cur = initNode;

        ListNode* lp = head;
        ListNode* rp = head;

        // 快慢指针
        int i;
        for (i=0; i<(right-left); i++) {
            rp = rp->next;
        }
        for (i=0; i<left-1; i++) {
            cur = cur->next;
            lp = lp->next;
            rp = rp->next;
        }
        ListNode* succ = rp->next;

        // 反转lp-rp之间的节点
        reversePart(lp, rp);

    }
};


