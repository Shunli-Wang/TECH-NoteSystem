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
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) {return head;} // 过滤空节点和单节点情况

        ListNode* initNode = new ListNode(0);
        initNode->next = head;
        ListNode* cur = initNode; // 变动指针cur
        ListNode* tmp = NULL; // 保持指针tmp

        while (head != NULL && head->next != NULL) { // 特殊结尾情况，单链表双链表全考虑到
            // 这些逻辑需要具体画图一步步实现，不能偷懒
            tmp = head;
            head = head->next;
            cur->next = head;
            tmp->next = head->next;
            head->next = tmp;
            // 跳转同样也需要一步步走
            cur = cur->next->next;
            head = head->next->next;
        }
        return initNode->next;
    }
};
