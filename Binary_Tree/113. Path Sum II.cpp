/*
113. Path Sum II
*/

class Solution {
    vector<int> onpath;
    vector<vector<int>> ans;
    int sum = 0;
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        traverse(root, targetSum);

        return ans;
    }
    void traverse(TreeNode* root, int targetSum){
        if(root == nullptr) return;



        onpath.push_back(root->val);
        sum += root->val;
        if(root->left == nullptr && root->right == nullptr && sum == targetSum){
            ans.push_back(onpath);
        }
        traverse(root->left, targetSum);
        traverse(root->right, targetSum);


        onpath.pop_back();
        sum -=root->val;
    }
};

/*
解題思路 邊走邊紀錄節點 如果數值對 就把此路徑加入解答
tc: o(n) sc:o(h) 
*/
