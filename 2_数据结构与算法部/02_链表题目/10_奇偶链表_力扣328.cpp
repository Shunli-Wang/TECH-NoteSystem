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
    ListNode* oddEvenList(ListNode* head) {
        if (head == NULL || head->next == NULL) {return head;}

        ListNode* initNode1 = new ListNode(0);
        ListNode* cur1 = initNode1;
        ListNode* initNode2 = new ListNode(0);
        ListNode* cur2 = initNode2;

        int cnt = 1;
        while (head != NULL) {
            if (cnt % 2 == 1) { // 奇数
                cur1->next = head;
                cur1 = cur1->next;
            } else { // 偶数
                cur2->next = head;
                cur2 = cur2->next;
            }
            head = head->next; cnt++;
        }
        cur2->next = NULL; // 尾端置空
        cur1->next = initNode2->next; // 最终的节点连接

        ListNode* res = initNode1->next;
        delete initNode1; delete initNode2;
        return res;
    }
};

