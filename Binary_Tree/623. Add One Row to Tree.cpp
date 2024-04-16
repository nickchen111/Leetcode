/*
623. Add One Row to Tree
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if(depth == 1){
            TreeNode* node = new TreeNode(val);
            node->left = root;
            return node;
        }

        DFS(NULL, root, val, depth, 1, -1);// 0代表左邊 1 代表右邊

        return root;
    }
    void DFS(TreeNode* prev, TreeNode* root, int val, int depth, int cur, int flag){
       
        if(cur == depth){
            TreeNode* node = new TreeNode(val);
            if(flag == 0){
                prev->left = node;
                node->left = root;
                return;
            }
            else {
                prev->right = node;
                node->right = root;
                return;
            }
        }
        if(root == NULL) return;

        DFS(root, root->left, val, depth, cur+1, 0);
        DFS(root, root->right, val, depth, cur+1, 1);

    }
};
