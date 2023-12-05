/*
1110. Delete Nodes And Return Forest
*/

// TC:O(n) SC:O(h+k)
class Solution {
    vector<TreeNode*> res;
    unordered_set<int> set;
    
    TreeNode* DFS(TreeNode* root){
        if(root == NULL) return NULL;
        //要接上左邊右邊之前先將他們清乾淨
        root->left = DFS(root->left);
        root->right = DFS(root->right);
        if(set.find(root->val) != set.end()){
            if(root->left) res.push_back(root->left);
            if(root->right) res.push_back(root->right);
            return NULL;
        }

        return root;

    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        if(root == NULL) return res;
        for(auto num:to_delete){
            set.insert(num);
        }

        if(DFS(root)) res.push_back(root);

        return res;
    }
};
