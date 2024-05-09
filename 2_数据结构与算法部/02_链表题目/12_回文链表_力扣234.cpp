// https://leetcode.cn/problems/palindrome-linked-list/
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
    // 笔试做法：使用栈直接完成
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next == NULL) {return true;}
        stack<int> stk;
        ListNode* p = head;
        while (p!=NULL) {
            stk.push(p->val);
            p = p->next;
        }
        int temp = 0;
        while (head!=NULL) {
            temp = stk.top(); stk.pop();
            if (head->val != temp) { // 但凡有1个不等，直接返回false
                return false;
            }
            head = head->next;
        }
        return true;
    }

    // 面试做法：找到中点改指向，一同中间走逐个判定，最后再把链表改回来
    ListNode* reverse(ListNode* head) {
        if (head->next == NULL) return head;
        ListNode* myNext = reverse(head->next); // [2]->[1]中，[2]可以直接获取[1]节点
        myNext->next = head;
        return head;
    }
    bool isPalindrome(ListNode* head) {
        if (head == NULL || head->next == NULL) return true;
        // 快慢指针找中点
        ListNode* slow = head;
        ListNode* fast = head;
        int cntHalf = 0;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            cntHalf++;
        }
        // 奇数情况：slow在中点
        // 偶数情况：slow在中点靠右

        // 捕获尾节点
        ListNode* tail = head;
        while (tail->next != NULL) {tail = tail->next;}
        // 反转链表
        reverse(slow)->next = NULL; // 逆转所有后半截链表
        // 循环判断
        ListNode* p1 = head;
        ListNode* p2 = tail;
        bool ans = true;
        for (int i=0; i<cntHalf; i++) {
            if (p1->val != p2->val) { 
                ans = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        // 再把链表改回来
        reverse(tail)->next = NULL;
        return ans;
    }

};
