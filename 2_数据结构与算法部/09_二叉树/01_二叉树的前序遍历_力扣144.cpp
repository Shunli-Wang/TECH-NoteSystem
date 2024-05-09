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
    void preOrder(TreeNode* root, vector<int>& arr) { // 中左右
        if (root == nullptr) {
            return ;
        }
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode* temp = stk.top(); stk.pop(); // 出来的顺序会变成中左右
            arr.push_back(temp->val);
            if (temp->right != nullptr) { // 先压右
                stk.push(temp->right);
            }
            if (temp->left != nullptr) { // 再压左
                stk.push(temp->left);
            }
        }
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        preOrder(root, ans);
        return ans;
    }

    /* 递归实现 */
    void process(TreeNode* node, vector<int>& arr) {
        if (node == nullptr) {
            return ;
        }
        arr.push_back(node->val);
        process(node->left, arr);
        process(node->right, arr);
    }
    vector<int> preorderTraversalRecurence(TreeNode* root) {
        vector<int> ans;
        process(root, ans);
        return ans;
    }
};
