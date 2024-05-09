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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL) {return head;}

        ListNode* initNode = new ListNode(0);
        initNode->next = head; // 当时忘记了链接初始head节点，低级错误

        ListNode* cur = initNode;
        ListNode* tmp = NULL;

        int record = -101; // 注意数字范围，不能让第一个节点出现误判

        while (head != NULL) {
            if (record == head->val) { // delete
                tmp = head;
                head = head->next;
                cur->next = head; // 报错
                delete tmp;
            } else { // keep
                record = head->val;
                head = head->next;
                cur = cur->next;
            }
        }

        ListNode* res = initNode->next;
        delete initNode;
        return res;
    }
};
