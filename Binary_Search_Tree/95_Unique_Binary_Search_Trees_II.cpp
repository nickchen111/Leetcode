/*
95. Unique Binary Search Trees II
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
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
