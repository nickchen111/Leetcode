/*
1448. Count Good Nodes in Binary Tree
*/

 
// DFS+ max_element  TC:O(n) SC:O(lgn)
class Solution {
public:
    int goodNodes(TreeNode* root) {
        if(root == NULL) return 0;
        vector<int> res;
        vector<int> temp;
        traverse(root,temp,res);

        return res.size()+1;
    }

    void traverse(TreeNode* root, vector<int>& temp, vector<int>& res){
        if(root == NULL) return;

        if(!temp.empty() && *max_element(temp.begin(),temp.end()) <= root->val){
            res.push_back(root->val);
        }   

        temp.push_back(root->val);
        traverse(root->left,temp, res);
        traverse(root->right,temp, res);
        temp.pop_back();
    }
};

// DFS  更簡潔寫法
class Solution {
    //DFS過程不斷帶著數值去做比較解法
    //如果一直是遞增序列就代表合格
public:
    int goodNodes(TreeNode* root) {
        if(root == NULL) return 0;
        if(root->left == NULL && root->right == NULL) return 1;

        return solve(root,INT_MIN);
    }

    int solve(TreeNode* root, int x){
        if(root == NULL) return 0;
        if(root->val >= x){
            return 1+solve(root->left, root->val)+solve(root->right,root->val);
        }

        //就算目前的點不及格 不保證他後面的也不及格
        return solve(root->left,x)+solve(root->right,x);

    }
};
