/*
2265. Count Nodes Equal to Average of Subtree
*/


// TC:O(n) SC:O(lgn)
class Solution {
    int count = 0;
public:
    int averageOfSubtree(TreeNode* root) {
        traverse(root);

        return count;
    }
    pair<int,int> traverse(TreeNode* root){
        if(root == NULL) return {0,0};

        auto left = traverse(root->left);
        auto right = traverse(root->right);
        int num = 1+left.first+right.first;
        int value = root->val + left.second + right.second;
        if(value/num == root->val) count+=1;

        return {num,value};
    }
};
