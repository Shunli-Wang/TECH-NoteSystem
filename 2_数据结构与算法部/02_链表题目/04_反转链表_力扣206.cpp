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

// 递归方法，还不会写 
class Solution {
public:

    ListNode* process(ListNode* head, ListNode* pre) {
        if (head->next == NULL) { // basecase
            head->next = pre;
            return head;
        }
        ListNode* tmp = head;

        ListNode* tmp = process(head->next, head);

        head->next = pre;
        return 
    }

    ListNode* reverseList(ListNode* head) {
        return process(head, NULL);
    }
};

class Solution { 
public:

    ListNode* reverseList(ListNode* head) { // 三指针方法，边界条件容易犯错误 
        if (head == NULL || head->next == NULL) {return head;}

        ListNode* pro = head->next;
        ListNode* past = NULL;

        while (pro != NULL) {
            head->next = past;
            past = head;
            head = pro;
            pro = pro->next;
        }
        head->next = past; // 最后pro指向NULL，head这里未设置，容易遗落
        return head;
    }
};

class Solution_1 {
public:
    ListNode* reverseList(ListNode* head) {
        // 空节点和单节点情况
        if (head == NULL || head->next == NULL) {return head;}
        
        // 压栈所有链表元素
        stack<ListNode*> stk;
        ListNode* p = head;
        while ( p!= NULL) {
            stk.push(p);
            p = p->next;
        }

        // init配合cur指针使用
        ListNode* initNode = new ListNode(0);
        ListNode* cur = initNode;

        // 依次弹栈，更改指针
        while (stk.size() != 0) {
            cur->next = stk.top(); 
            cur = cur->next;
            stk.pop(); 
        }
        cur->next = NULL; // 处理结尾指针
        return initNode->next; // 返回起始节点
    }
};

