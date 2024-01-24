/*
1457. Pseudo-Palindromic Paths in a Binary Tree
*/



// TC:O(n) SC:O(10+n)
class Solution {
    int res = 0;
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        if(root == NULL) return 0;
        if(root->left == NULL && root->right == NULL) return 1;

        vector<int> count(10,0);
        DFS(root, count);

        return res;
    }
    void DFS(TreeNode* root, vector<int>& count){
        if(root ->left == NULL && root->right == NULL){
            count[root->val] += 1;
            int times = 0;
            bool flag = 1;
            for(int i = 1; i <= 9; i++){
                if(count[i] % 2 == 1) times += 1;
                if(times >= 2) flag = 0;
            }
            if(flag) res += 1;
            count[root->val] -= 1;
            return;
        }

        count[root->val] += 1;
        if(root->left) DFS(root->left, count);
        if(root->right) DFS(root->right, count);
        count[root->val] -= 1;
    }
};

/*
判斷一棵樹的各種路徑有多少條root->leaf可以是回文
回文條件一個奇數 其他都是偶數 or 都是偶數
*/
