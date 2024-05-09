/* 2.两数相加 中等 */
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int a = 0;
        int b = 0;
        int store = 0;
        int plus = 0; // 进位信息

        ListNode* initHead = NULL; // 静态起始指针
        ListNode* cur = NULL; // 动态跟随指针
        ListNode* tmp = NULL;

        while (l1 != NULL || l2 != NULL) { // 走到两个都结束，实现逻辑上的对齐
            // 防止空值，获取真实数值
            a = l1 == NULL ? 0 : l1->val;
            b = l2 == NULL ? 0 : l2->val;
            
            // 进行计算
            store = a + b + plus;
            plus = store / 10; // 进位信息

            tmp = new ListNode(store % 10);
            if (initHead == NULL) {
                initHead = tmp;
                cur = tmp;
            } else {
                cur->next = tmp;
                cur = tmp;
            }

            // 进行更新
            l1 = l1 == NULL ? NULL : l1->next;
            l2 = l2 == NULL ? NULL : l2->next;
        }

        if (plus == 1) { // 考虑结束时候的进一
            tmp = new ListNode(1);
            cur->next = tmp;
        }

        return initHead;
    }
};


/* 
属于策略类的题目，和十进制计算结合在一起，要考虑进位问题。
- 考虑一长一短链表导致的补0问题
- 结束时候的进位要考虑额外添加
- 适合用静态initHead和动态cur结合的方法
 */

