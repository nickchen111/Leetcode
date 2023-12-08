/*
606. Construct String from Binary Tree
*/

// TC:O(n) SC:O(n)
class Solution {
    string res;
public:
    string tree2str(TreeNode* root) {
        if(root == NULL) return "";
        DFS(root);
        
        return res;
    }
    
    void DFS(TreeNode* root){
        if(root == NULL) return;

        res += to_string(root->val);
        
        //  左邊有東西自己要加入() 右邊有東西也要
        if(root->left || root->right){
            res += "(";
            DFS(root->left);
            res += ")";
        }
        if(root->right){
            res += "(";
            DFS(root->right);
            res += ")";
        }
    }
};
