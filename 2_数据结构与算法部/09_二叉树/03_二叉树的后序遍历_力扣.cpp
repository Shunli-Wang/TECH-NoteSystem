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
    /* 使用一个栈：这个方法使用了打印标记，后序有时间再梳理 */

    /* 使用两个栈，借助前序遍历的变种进行逆序 */
    void postOrder(TreeNode* root, vector<int>& arr) {
        if (root == nullptr) { // 防止程序崩溃
            return ;
        }
        stack<TreeNode*> stk, colect;
        stk.push(root);
        while (!stk.empty()) { // 前序遍历更改为：中右左
            root = stk.top(); stk.pop();
            colect.push(root);
            if (root->left != nullptr) {
                stk.push(root->left);
            }
            if (root->right != nullptr) {
                stk.push(root->right);
            }
        }
        while (!colect.empty()) { // 将中右左的顺序逆序，变成左右中，完成后序遍历
            root = colect.top(); colect.pop();
            arr.push_back(root->val);
        }
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        postOrder(root, ans);
        return ans;
    }

    /* 递归实现 */
    void process(TreeNode* node, vector<int>& arr) {
        if (node == nullptr) {
            return ;
        }
        process(node->left, arr);
        process(node->right, arr);
        arr.push_back(node->val);
    }
    vector<int> postorderTraversalRecurence(TreeNode* root) {
        vector<int> ans;
        process(root, ans);
        return ans;
    }
};



