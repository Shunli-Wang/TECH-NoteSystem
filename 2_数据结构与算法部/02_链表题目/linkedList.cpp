#include<iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

ListNode* head = new ListNode(5);

/* 203.移除链表元素 */
class Solution {
public:
    ListNode* removeList(ListNode* head, int val) {
        /* 两阶段方法 */
        // 头节点是目标值情况
        while (head != NULL && head->val == val) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }

        // 过程节点是目标值
        ListNode* cur = head;
        while (cur != NULL && cur->next != NULL) { // 遍历所有节点
            if (cur->next->val != val) { // 保留节点
                cur = cur->next;
            } else { // 删除节点
                ListNode * tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
        }
        return head;
    }

    ListNode* removeList_02(ListNode* head, int val) {
        /* 添加初始虚拟节点方法 */
        ListNode * virNode = new ListNode(0);
        virNode->next = head;

        // 直接使用正常的动态删除过程
        ListNode * cur = virNode;
        while(cur != NULL && cur->next != NULL) {
            if (cur->next->val == val) {
                ListNode * tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = virNode->next;
        delete virNode;

        return head;
    }
};

/* 206.反转链表 */
class Solution {
public:
    ListNode* reverseLinkedList(ListNode* head) {
        ListNode* p = head->next;
        head->next = NULL;

        while (p != NULL) {
            ListNode* tmp = p->next;
            p->next = head;
            head = p;
            p = tmp;
        }
        return head;
    }
};

/* 24.两两交换链表中的节点 */
class Solution {
public:
    ListNode* swapLinkedList(ListNode* head) {
        ListNode* initNode = new ListNode(0);
        initNode->next = head;

        ListNode* cur = initNode;
        while(cur->next != NULL && cur->next->next != NULL){ // 确定有两个后续节点 
            // 记录好这两个后续节点
            ListNode* tmp0 = cur->next;
            ListNode* tmp1 = cur->next->next;
            ListNode* tmp2 = cur->next->next->next;

            cur->next = tmp1;
            tmp1->next = tmp0;
            tmp0->next = tmp2;

            cur = cur->next->next;
        }
        return initNode->next;
    }
};

/* 19.删除链表的倒数第N个节点 */
class Solution {
public:
    ListNode* deleteNthNode(ListNode* head, int N) {
        ListNode* initNode = new ListNode(0);
        initNode->next = head;
        ListNode* fast = initNode;
        ListNode* slow = initNode;

        for(int i=0; i<N; i++) {
            fast = fast->next;
        }

        while(fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        // 此时slow指向删除的前一个元素
        ListNode* cur = slow->next;
        slow->next = cur->next;
        delete cur;

        return initNode->next;
    }
};

/* 面试题 02.07. 链表相交 */
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        // 统计两个链表长度
        ListNode* pA = headA;
        ListNode* pB = headB;
        int cntA = 0;
        int cntB = 0;
        while(pA != NULL) {pA = pA->next; cntA++;}
        while(pB != NULL) {pB = pB->next; cntB++;}

        // 指向相同起步位置
        ListNode* longList = NULL;
        ListNode* shortList = NULL;
        if (cntA == cntB) {
            longList = headA;
            shortList = headB;
        } else {
            longList = cntA > cntB ? headA : headB;
            shortList = cntA > cntB ? headB : headA;
            int steps = cntA > cntB ? cntA-cntB : cntB-cntA;
            for (int i=0; i<steps; i++) {
                longList = longList->next;
            }
        }

        // 开始同步评判
        while(longList != NULL) {
            if (longList == shortList) {
                return longList;
            }
            longList = longList->next;
            shortList = shortList->next;
        }
        return NULL;
    }
};

/* 141. 环形链表 */
#include<unordered_set>
// 使用unordered_set集合处理
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> set;
        while (head != NULL) {
            if (set.count(head)) {
                return true;
            }
            set.insert(head);
            head = head->next;
        }
        return false;
    }
};
// 使用佛洛依德判圈法
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) {return false;}

        ListNode * slow = head->next;
        ListNode * fast = head->next->next;

        while (slow != fast) {
            if (fast == NULL || fast->next == NULL) {return false;}
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};




/* 142. 环形链表 II */
class Solution{
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == NULL || head->next == NULL) {return NULL;}

        ListNode* slow = head->next;
        ListNode* fast = head->next->next;

        while (slow != fast) {
            if (fast == NULL || fast->next == NULL || fast->next->next == NULL) {return NULL;} // 一旦有NULL直接return，一定是无环链表
            slow = slow->next;
            fast = fast->next->next;
        }

        // 能运行到这里一定是 slow == fast
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};

/* 287. 寻找重复数 */
#include<vector>
#include<unordered_map>
// 解法1：使用set直接解，但是空间复杂度是O(N)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_map<int, bool> map;
        for(int num: nums) {
            if (map[num]) {return num;}
            map[num] = true;
        }
        return -1;
    }
};
// 解法2：使用弗洛伊德判圈法，将数组的数值作为下标索引，寻找入环节点
// —————— 这个思路非常惊艳，因为数组本身定义的时候就埋下了雷，n+1个数，范围是1-n，应当很自然的想到使用下标进行索引。
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 寻找第一次碰面
        int slow = nums[0]; // 走1步
        int fast = nums[nums[0]]; // 走2步
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        // 到达了碰面地方
        fast = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return fast;
    }
};


/* 86. 分隔链表 */
// 使用Init节点进行两个分支链表的构建
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

/* 206. 反转链表 */
#include<stack>
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

    }
};

/* 92. 反转链表 II */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

    }
};

/* 234. 回文链表 */
#include<stack>
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<ListNode*> listStack;
        ListNode* cur = head;
        while (cur != NULL) {
            listStack.push(cur);
            cur = cur->next;
        }
        cur = head;
        while (~listStack.empty()) {
            if (cur->val != listStack.top()->val) {
                return false;
            }
        }
        return true;
    }
};


/* 2. 两数相加 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int a = 0;
        int b = 0;
        int add = 0;
        int plus = 0;

        ListNode* head = NULL;
        ListNode* pre = NULL;
        ListNode* tmp = NULL;

        while (l1 != NULL || l2 != NULL) {
            // 处理为0情况
            a = (l1 == NULL) ? 0 : l1->val;
            b = (l2 == NULL) ? 0 : l2->val;

            add = a + b + plus;
            plus = add / 10; // 下一层进位
            tmp = new ListNode(add % 10); // 这一层数字

            if (head == NULL) {
                head = tmp;
                pre = tmp;
            } else {
                pre->next = tmp;
                pre = tmp;
            }

            // 处理链表末尾情况
            l1 = (l1 == NULL) ? NULL : l1->next;
            l2 = (l2 == NULL) ? NULL : l2->next;
        }
        // 链表遍历完结，但是还有一个进位项，例如115+115=2201，需要额外处理
        if (plus == 1) {
            tmp = new ListNode(1);
            pre->next = tmp;
        }
        // 直接返回头节点
        return head;
    }
};


/* 19. 删除链表的倒数第 N 个结点 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL) {
            return NULL;
        }
        if (head->next == NULL && n == 1) {
            return NULL;
        }

        ListNode* initNode = new ListNode(0);
        initNode->next = head;

        ListNode* tail = initNode; // 尾指针，压中最后一个元素
        ListNode* pre = initNode; // 前指针，和流动指针差1
        ListNode* cur = head; // 流动指针
        
        // tail从init先走N步，或者从head先走n-1步
        for (int i=0 ; i < n; i++) {
            tail = tail->next;
        }

        // tail压末尾节点，cur压删除节点，pre压删除节点的前节点
        while (tail->next != NULL) {
            pre = pre->next;
            cur = cur->next;
            tail = tail->next;
        }

        // 
        pre->next = cur->next;
        delete cur;

        return initNode->next; // 考虑头节点被删除的情况，返回initNode的next指针
    }
};


/* 21. 合并两个有序链表 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1==NULL && list2==NULL) {return NULL;}
        if (list1==NULL || list2==NULL) {return list1 == NULL ? list2 : list1;}

        ListNode* initNode = new ListNode(0);
        ListNode* cur = initNode;

        while (list1 != NULL && list2 != NULL) {
            if (list1->val < list2->val) {
                cur->next = list1;
                list1 = list1->next;
            } else {
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next;
        }

        cur->next = list1 == NULL ? list2 : list1;
        return initNode->next;
    }
};


/* 23. 合并 K 个升序链表 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int len = lists.size();
        ListNode* listArr[len];
        

        for (int i=0; i<lists.size(); i++) {
            lists[i]
        }
    }
};















