/*
129. Sum Root to Leaf Numbers
*/

// TC:O(n) SC:O(n)
class Solution {
    int res = 0;
public:
    int sumNumbers(TreeNode* root) {
        if(root == NULL) return 0;
        string str="";
        DFS(root,str);

        return res;
    }
    void DFS(TreeNode* node, string str){
        if(node->left == NULL && node->right == NULL){
            string ch = to_string(node->val);
            str = str + ch;
            res += stoi(str);
            return;
        } 
        
        string ch = to_string(node->val);
        str = str + ch;
        if(node->left) DFS(node->left, str);
        if(node->right) DFS(node->right, str);
    }
};
