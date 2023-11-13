/*
701. Insert into a Binary Search Tree
*/

// Recursion TC:O(h) SC:O(h)
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr) return new TreeNode(val);

        if(root->val > val) {
            root->left = insertIntoBST(root->left, val);
        }

        if(root-> val < val) {
            root->right = insertIntoBST(root->right, val);
        }

        return root;
    }
};

/*
二叉搜索樹中的增：插入一個數字 
往左或者往右子樹去找 直到指導適當的位置 最後return root就是把沒找到的那些點return接回去 
找到時root會等於空 就會新增點上去
*/
