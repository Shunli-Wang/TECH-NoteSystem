// https://leetcode.cn/problems/binary-tree-level-order-traversal/solutions/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return ans;

        queue<TreeNode*> que; // 宽度优先遍历用队列
        que.push(root);
        int cnt; // 数量快照变量

        while (!que.empty()) {
            cnt = que.size(); // 快照，控制循环次数
            vector<int> tempArr(cnt, 0);
            for (int i=0; i<cnt; i++) {
                TreeNode* cur = que.front(); que.pop(); // 弹出当前节点，进行记录处理
                tempArr[i] = cur->val;
                if (cur->left != nullptr)  que.push(cur->left);
                if (cur->right != nullptr)  que.push(cur->right);
            }
            ans.push_back(tempArr);
        }
        return ans;
    }
};


// 层序遍历的类似题目，都比较简单，只是简单变种
// LeetCode 103. Binary Tree Zigzag Level Order Traversal 之字形层序遍历
// LeetCode 199. Binary Tree Right Side View 找每一层的最右结点
// LeetCode 515. Find Largest Value in Each Tree Row 计算每一层的最大值
// LeetCode 637. Average of Levels in Binary Tree 计算每一层的平均值

