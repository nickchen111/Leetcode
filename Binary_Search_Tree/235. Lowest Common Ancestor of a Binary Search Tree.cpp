/*
235. Lowest Common Ancestor of a Binary Search Tree
*/

// TC:O(n) SC:O(lgn)
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root->val == p->val || root->val == q->val) return root;

        else if(root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
        else if(root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);

        return root;
    }
};

// old
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        if(root == nullptr) return nullptr;

        return traverse(root, p, q);
    }

    TreeNode* traverse(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root->val > p->val && root->val > q->val){
            return traverse(root->left, p, q);
        }
        else if(root->val < p->val && root->val < q->val){
            return traverse(root->right, p, q);
        }

        else return root;
    }

};

/*
解題思維：
變成bst求LCA
case 1 兩點的值都比root大 說明在右邊子樹  
case 2 兩點的值都比root小 說明在左邊子樹 
case 3 兩點的值一個在左一個在右 左右子樹各有一個 
tc: o(n) sc: o(lgn)
*/
