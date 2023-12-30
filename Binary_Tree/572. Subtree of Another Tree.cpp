/*
572. Subtree of Another Tree
*/


// BFS TC:O(m*n) SC:O(max(m,n))
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        //我的想法是先遍歷root 一但有跟sub一樣的數值就開始比較 is same tree?
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* cur = q.front();
            q.pop();
            if(cur->val == subRoot->val){
                if(isSameTree(cur,subRoot)) return true;
            }
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
        }

        return false;
    }

    bool isSameTree(TreeNode* p, TreeNode* q){
        if(!p && !q) return true;
        if(!p || !q) return false;
        if(p->val != q->val) return false;

        return isSameTree(p->left,q->left) && isSameTree(p->right, q->right);
    }
};

//recursion TC:O(m*n) SC:O(max(m,n))
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) { 
        if(root == NULL) return false;

        if(isSameTree(root, subRoot)) return true;

        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

    bool isSameTree(TreeNode* p, TreeNode* q){
        if(p == NULL && q == NULL) return true;
        if(p == NULL || q == NULL) return false;

        if(p->val != q->val) return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

//KMP TC:O(m+n) SC:O(m+n)
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        //母子樹都轉成數組 轉的方式必須是前序或者後序 然後就可以用KMP
        vector<int> S,T;
        convert(root,S);
        convert(subRoot, T);
        vector<int> suffix =preprocess(T);
        int n = S.size();
        int m = T.size();
        vector<int> dp(n,0);
        dp[0] = (S[0]==T[0]);
        for(int i = 1; i<n; i++){
            int j = dp[i-1];
            while(j > 0 && S[i] != T[j]){
                j = suffix[j-1];
            }
            dp[i] = j + (S[i] == T[j]);
            if(dp[i] == T.size()) return true;
        }

        return false;
    }
    void convert(TreeNode* root, vector<int>& arr){
        if(root== NULL){
            arr.push_back(INT_MAX);
            return;
        }
        //前序遍歷
        arr.push_back(root->val);
        convert(root->left,arr);
        convert(root->right,arr);
    }

    vector<int> preprocess(vector<int>& T){
        int n = T.size();
        vector<int> suffix(n,0);
        suffix[0] = 0;
        for(int i = 1; i<n; i++){
            int j = suffix[i-1];
            while(j>0 && T[i] != T[j]){
                j = suffix[j-1];
            }
            suffix[i] = j + (T[i] == T[j]);
        }

        return suffix;
    }
};

