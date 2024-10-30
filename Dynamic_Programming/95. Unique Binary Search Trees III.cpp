/*
95. Unique Binary Search Trees II
*/

// 區間 DP + memo  TC:O(n^3) SC:O(n^3)
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {

        vector<vector<vector<TreeNode*>>> memo(n+2, vector<vector<TreeNode*>>(n+2, vector<TreeNode*>()));
        function<vector<TreeNode*>(int l, int r)> dfs = [&](int l, int r) -> vector<TreeNode*> {
            if(l > r) return {NULL};
            if(l == r) return {new TreeNode(l)};
            if(!memo[l][r].empty()) return memo[l][r];

            vector<TreeNode*> res;
            for(int i = l; i <= r; i++) {
                vector<TreeNode*> left = dfs(l,i-1);
                vector<TreeNode*> right = dfs(i+1, r);
                for(auto x : left) {
                    for(auto y : right) {
                        TreeNode* root = new TreeNode(i);
                        root->left = x;
                        root->right = y;
                        res.push_back(root);
                    }
                }
            }

            return memo[l][r] = res;
        };

        return dfs(1, n);
    }
};

// TC SC: O(4^n / n^(3/2))
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n == 0) return {};

        return build(1, n);
    }
    vector<TreeNode*> build(int lo, int hi){
        vector<TreeNode*> ans;
        if(lo > hi){ //到底的時候要加上nullptr
            ans.push_back(nullptr);
            return ans;
        }

        //窮舉所有root 的可能性
        for(int i = lo; i<=hi; i++){//此i即為root
            //遞歸構造出所有左右子樹的合法bst
            vector<TreeNode*> lefttree = build(lo, i-1);
            vector<TreeNode*> righttree= build(i+1, hi);


            //給root節點窮舉所有可能的左右樹的組合 有點類似96題的左邊右邊可能性相乘
            for(auto left:lefttree){
                for(auto right:righttree){
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
};
/*
tc sc: O(4^n / n^(3/2))
*/
