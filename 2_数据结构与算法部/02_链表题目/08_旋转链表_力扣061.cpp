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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL) {return head;}
        // 一开始写了虚拟节点，但是最后发现可以删除，所以才有了这个简介代码

        ListNode* tail = head;
        int len = 1;
        while (tail->next != NULL) {
            tail = tail->next;
            len++;
        }
        tail->next = head;

        for (int i=0; i<(len-k%len); i++) { //  移动多少次? L-k%L，规律需要画出来
            head = head->next;
            tail = tail->next;
        }
        tail->next  = NULL;
        return head;
    }
};
