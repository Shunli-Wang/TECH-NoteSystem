// https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return ans;

        queue<TreeNode*> que;
        que.push(root);
        int cnt;
        bool reverse = false;

        while (!que.empty()) {
            // 正常的BFS，依次排好顺序
            cnt = que.size();
            vector<int> tempArr;
            for (int i=0; i<cnt; i++) {
                TreeNode* cur = que.front(); que.pop();
                tempArr.push_back(cur->val);
                if (cur->left != nullptr)  que.push(cur->left);
                if (cur->right != nullptr)  que.push(cur->right);
            }

            // 如果真的需要反转此轮，进行
            if (reverse) {
                vector<int> tempArrR(cnt);
                for (int j=0; j<cnt; j++) {
                    tempArrR[j] = tempArr[cnt-1-j];
                }
                tempArr = tempArrR;
            }

            ans.push_back(tempArr); // 记录结果
            reverse = !reverse; // 反转状态
        }
        return ans;
    }
};
