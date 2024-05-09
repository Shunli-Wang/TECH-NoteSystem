#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /* 非递归实现 */
    void inOrder(TreeNode* root, vector<int>& arr) { // 左中右
        if (root == nullptr) {
            return ;
        }
        stack<TreeNode*> stk;
        // !!! 这个逻辑配合太完美了，栈空||此节点不为空 进行循环，刚好筛选出两种情况分别处理。
        while (!stk.empty() || root != nullptr) {
            if (root != nullptr) { // 非空节点，压入自身后处理左孩子
                stk.push(root);
                root = root->left;
            } else { // 到达空节点，弹栈赋予root节点，打印，右树开始准备循环
                root = stk.top(); stk.pop();
                arr.push_back(root->val);
                root = root->right;
            }
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        inOrder(root, ans);
        return ans;
    }

    /* 递归实现 */
    void process(TreeNode* node, vector<int>& arr) {
        if (node == nullptr) {
            return ;
        }
        process(node->left, arr);
        arr.push_back(node->val);
        process(node->right, arr);
    }
    vector<int> inorderTraversalRecurence(TreeNode* root) {
        vector<int> ans;
        process(root, ans);
        return ans;
    }
};

// 1. 来到子树的头，一直让左边界进栈，直到左边界遍历完
// 2. 从栈里弹出结点，打印，此节点的右树重复步骤1
// 3. 直到没有子树并且栈空了

// 本质：用左树分解整棵二叉树
