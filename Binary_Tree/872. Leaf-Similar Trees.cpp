/*
872. Leaf-Similar Trees
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> arr1;
        DFS(root1,arr1);
        vector<int> arr2;
        DFS(root2,arr2);
        
        
        return arr1 == arr2;
    }
    void DFS(TreeNode* root, vector<int>& arr){
        if(root == NULL){
            return;
        }

        if(root->left == NULL && root->right == NULL){
            arr.push_back(root->val);
        }
        DFS(root->left, arr);
        DFS(root->right, arr);
    }
    
};
