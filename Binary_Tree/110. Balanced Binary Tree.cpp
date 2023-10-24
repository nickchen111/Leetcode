/*
110. Balanced Binary Tree
*/


// 計算每個子樹高度差的方法 TC:O(nlgn) SC:O(lgn)
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(root==NULL) return true;
        
        //求左右兩邊最大深度
        int left = traverse(root->left);
        int right = traverse(root->right);
        if(abs(left-right) > 1) return false;

        //還需判斷他的子樹是否也是平衡的
        return isBalanced(root->left) && isBalanced(root->right);
    }
    int traverse(TreeNode* root){
        if(root==NULL) return 0;
        return 1+max(traverse(root->left),traverse(root->right));
    }
};

//優化  TC:O(n) SC:O(lgn)
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(root==NULL) return true;
    
        bool balanced = true;
        traverse(root, balanced);
    
        return balanced;
    }
    int traverse(TreeNode* root, bool& balanced){
        if(root==NULL) return 0;
        int left = traverse(root->left,balanced);
        int right = traverse(root->right, balanced);
        if(abs(left-right) > 1){
            balanced = false;
            return -1;
        } 
        return 1+max(left,right);
    }
};
