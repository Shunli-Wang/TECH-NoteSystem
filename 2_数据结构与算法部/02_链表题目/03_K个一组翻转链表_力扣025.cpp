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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL) {return NULL;}
        ListNode* p = head; // 统计长度，需要浪费掉一个指针
        int len = 0;
        while (p != NULL) {  // 使用压空方法，获取到链表长度
            len++;
            p = p->next;
        }
        if (len < k) {return head;} // 捣乱的数据，直接清洗掉

        ListNode* initNode = new ListNode(0); // 创建init节点
        ListNode* cur = initNode; // 遍历指针初始化可以考虑指向init节点，方便操作

        stack<ListNode*> stk;
        for (int i = 0; i < len/k; i++) { // 进行i次反转操作
            for (int in = 0; in < k; in++) { // 入栈k个
                stk.push(head);
                head = head->next;
            }
            for (int out = 0; out < k; out++) { // 出栈k个,做好自动衔接
                cur->next = stk.top();
                cur = cur->next;
                stk.pop();
            }
        }
        cur->next = head; // 结束循环时head压再末尾元素，直接修改cur指针的next即可
        return initNode->next;
    }
};

// 使用stack的方法比较鸡贼
// 比较高级的做法？
