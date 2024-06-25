/*
1038. Binary Search Tree to Greater Sum Tree
*/

// TC:O(n) SC:O(n) 
class Solution {
    int pre = 0;
public:
    TreeNode* bstToGst(TreeNode* root) {
        if (root->right) bstToGst(root->right);
        pre = root->val = pre + root->val;
        if (root->left) bstToGst(root->left);
        return root;
    }
};

//次佳解 TC:O(nlgn) SC:O(n) 
class Solution {
    vector<int> arr;
    vector<int> presum;
    int index[101];
    int n;
public:
    TreeNode* bstToGst(TreeNode* root) {
        if(root == NULL) return NULL;
        DFS(root);
        sort(arr.begin(), arr.end());
        n = arr.size();
        presum.resize(n);
        
        index[arr[0]] = 0;
        presum[0] = arr[0];
        for(int i = 1; i < n; i++){
            presum[i] = presum[i-1] + arr[i];
            index[arr[i]] = i;
        }
        DFS2(root);

        return root;
    }
    void DFS(TreeNode* node){
        if(node == NULL) return;
        arr.push_back(node->val);
        DFS(node->left);
        DFS(node->right);
    }
    void DFS2(TreeNode* node){
        if(node == NULL) return;
        
        node->val += (presum[n-1] - presum[index[node->val]]);
        DFS2(node->left);
        DFS2(node->right);
    }
};
