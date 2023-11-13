/*
538. Convert BST to Greater Tree
*/

// Recursion TC:O(n) SC:O(lgn)
class Solution {
    int sum = 0;
public:
    TreeNode* convertBST(TreeNode* root) {
        // 節點按照inorder順序
        if(root == NULL) return NULL;
        traverse(root);

        return root;
    }
    void traverse(TreeNode* root){

        if(root==NULL) return;
        traverse(root->right);
        sum+=root->val;
        root->val =sum;
        traverse(root->left);
    }
};

// Stack TC:O(n) SC:O(lgn)
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        if(root==NULL) return NULL;
        stack<TreeNode*> stack;
        int sum = 0;
        TreeNode* cur = root;
        while(!stack.empty() || cur){
            while(cur != NULL){
                stack.push(cur);
                cur = cur->right;
            }
            TreeNode* node = stack.top();
            stack.pop();
            sum+=node->val;
            node->val = sum;
            cur = node->left;
        }

        return root;
    }
};
