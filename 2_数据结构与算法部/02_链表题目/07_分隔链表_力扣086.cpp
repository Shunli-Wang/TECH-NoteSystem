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
    ListNode* partition(ListNode* head, int x) {
        ListNode* small = new ListNode(0);
        ListNode* smallHead = small; // 存储静态0节点

        ListNode* large = new ListNode(0);
        ListNode* largeHead = large; // 存储静态0节点

        while (head != NULL) {
            if (head->val < x) {
                small->next = head;
                small = head;
            } else {
                large->next = head;
                large = head;
            }
            head = head->next;
        } // 结束之后分别构建好了两个链表，small和large指向最后一个元素

        small->next = largeHead->next; // 链接链表
        large->next = NULL;

        return smallHead->next;
    }
};
