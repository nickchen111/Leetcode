// TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        /*
        這題要有一個觀念是LCA一定出現在他的兩個分支往下會是最大深度，但是如example1的 1節點 假設先traverse到他
        更新他為最大深度，但其實他不是答案，所以會根據當前最大深度的不斷更新也更新答案
        */
        if (root == NULL) return NULL;
        TreeNode* ans;
        int mxD = 0;
        auto dfs = [&](auto &&dfs, TreeNode* node, int d) -> int {
            if (node == NULL) {
                mxD = max(d, mxD);
                return d;
            }
            int leftD = dfs(dfs, node->left, d + 1);
            int rightD = dfs(dfs, node->right, d + 1);
            if (leftD == rightD && leftD == mxD) {
                ans = node;
            }
            return max(leftD, rightD);
        };
        dfs(dfs, root, 1);
        return ans;

    }
};
