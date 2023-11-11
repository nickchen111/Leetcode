/*
1448. Count Good Nodes in Binary Tree
*/

// TC:O(n) SC:O(lgn) 11/11
class Solution {
    int res = 0;
public:
    int goodNodes(TreeNode* root) {
        //preorder + DFS
        DFS(root,root->val);
        return res;
    }

    void DFS(TreeNode* root,int maxNum){
        if(root == NULL) return;

        if(root->val >= maxNum) res+=1;

        maxNum = max(maxNum, root->val);
        DFS(root->left,maxNum);
        DFS(root->right,maxNum);
    }
};

 
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

//BFS
class Solution {
public:
    int goodNodes(TreeNode* root) {
        //BFS
        if(root == NULL) return 0;
        queue<pair<TreeNode*,int>> q;
        int maxNum = INT_MIN;
        q.push({root,maxNum});
        int res = 0;
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i < sz; i++){
                int num = q.front().second;
                TreeNode* node = q.front().first;
                q.pop();
                if(node->val >= num){
                    res+=1;
                    if(node->left) q.push({node->left,node->val});
                    if(node->right) q.push({node->right,node->val});
                }
                else{
                    if(node->left) q.push({node->left,num});
                    if(node->right) q.push({node->right,num});
                }
            }
        }

        return res;
    }
};
