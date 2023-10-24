/*
538. Convert BST to Greater Tree
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    int sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        traverse(root);

        return root;
    }
    void traverse(TreeNode* root){

        if(root == nullptr) return;

        traverse(root->right); //反過來traverse就會是由大到小
        sum +=root->val;
        root->val = sum;
        traverse(root->left);
    }
};
/*
解題思路
此題希望你將二叉搜索性轉成累加樹
去思考bst的特性即中序遍歷會是他的由小到大數組 既然如此
我們就由大到小遍歷 在中序的地方去加總數值然後放進去root裡
tc: o(n) sc: o(h) h = lgn ~n
*/
