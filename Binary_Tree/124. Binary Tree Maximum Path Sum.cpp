/*
124. Binary Tree Maximum Path Sum
*/

// 1125 TC:O(n) SC:O(n)
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        auto dfs = [&](auto &&dfs, TreeNode* node) -> int {
            if(node == NULL) return 0;
            int left = dfs(dfs, node->left);
            int right = dfs(dfs, node->right);
            res = max({res, node->val + left + right, node->val + left, node->val + right, node->val});
            return max(node->val, node->val + max(left, right));
        };
        dfs(dfs,root);

        return res;
    }
};

//TC:O(n) SC:O(n)
class Solution {
    int res = INT_MIN;
public:
    int maxPathSum(TreeNode* root) {
        if(root ==NULL) return 0;
        
        traverse(root);
        return res;
    }
    int traverse(TreeNode* root){
        //自己是個拐點 or 只是別人順路的狀態
        if(root == NULL) return 0;
        int left = traverse(root->left);
        int right = traverse(root->right);

        //當拐點情況
        int maxSum = root->val;
        if(left >= 0) maxSum+=left;
        if(right >= 0) maxSum+=right;
        res = max(res, maxSum);

        if(left < 0 && right < 0) return root->val;

        return root->val+max(left,right);

    }
};
