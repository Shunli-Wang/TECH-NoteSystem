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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL) { // 过滤空列表
            return NULL;
        }
        if (head->next == NULL && n == 1) { // 过滤删除单节点情况
            return NULL;
        }

        ListNode* initHead = new ListNode(0);
        initHead->next = head;

        // 声明辅助指针，使用三指针卡位置
        ListNode* pre = initHead; // 初始0节点
        ListNode* cur = head; // 变动节点
        ListNode* tail = initHead; // 尾部节点

        // tail先走N步，和cur建立空间差n-1
        for (int i=0; i < n; i++) {
            tail = tail->next;
        }

        // tail压最后一个元素，pre & cur & tail同步移动，压住时停止
        while (tail->next != NULL) {
            tail = tail->next;
            cur = cur->next;
            pre = pre->next;
        }

        // 开始更改删除节点
        pre->next = cur->next;
        delete cur;

        return initHead->next; // 首个节点可能被删除，要考虑到
    }
};