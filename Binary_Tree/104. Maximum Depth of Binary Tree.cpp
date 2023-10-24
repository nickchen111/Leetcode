/*
104. Maximum Depth of Binary Tree

*/

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
//此題是想求一棵二元樹的深度為何
//DFS TC:O(n) SC:O(h)
class Solution1 {
public:
    int maxDepth(TreeNode* root) {
        int ans = 0;
        if(root == nullptr) return 0;
        ans = dfs(root, 1);

        return ans;
    }
    int dfs(TreeNode* root, int ans){
        if(root == nullptr) return ans-1;
        int left = dfs(root->left, ans+1);
        int right = dfs(root->right, ans+1);
        

        return (left >= right) ? left:right;
    }
};
//更快的DFS寫法 Time Complexity: O (n) Space Complexity: O (h)
class Solution1 {
public:
int maxDepth(TreeNode* root) {
		if (root==NULL) return 0; 
		return max(maxDepth(root->left)+1, maxDepth(root->right)+1);
}
};
/*
解題思維
1.算左邊跟算右邊分別有多深
2. 所以使用遞歸 最後再去判斷left 跟right哪個大
*/

//BFS TC:O(n) SC:O(w) w為底層寬度
class Solution {
public:
    int maxDepth(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        if(root == nullptr) return 0;
        while(!q.empty()){
            depth++;
            int n = q.size();
            for(int i = 0; i < n; i++){
                TreeNode* node = q.front();
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return depth;
    }
};


/*
1. 使用bfs時 每個回圈去count++一次
2. 用queue來判斷是否該停止
*/

