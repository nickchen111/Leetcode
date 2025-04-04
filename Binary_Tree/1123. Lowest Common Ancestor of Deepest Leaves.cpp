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

//做法2
class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        /*
        這題要有一個觀念是LCA一定出現在他的兩個分支往下會是最大深度，但是如example1的 1節點 假設先traverse到他
        更新他為最大深度，但其實他不是答案，所以會根據當前最大深度的不斷更新也更新答案
        做法2 是直接以每個樹為判斷，如果他左子樹高度大於右子樹 那麼LCA在左子樹 反之在右子樹
        如果高度相同就回傳當前節點為當下該子節點的lca，一路傳上去就知道以根為樹的狀況lca為何
        */
        auto dfs = [&](auto &&dfs, TreeNode *node) -> pair<int, TreeNode*> {
            if (node == nullptr)
                return {0, nullptr};
            auto [left_height, left_lca] = dfs(dfs, node->left);
            auto [right_height, right_lca] = dfs(dfs, node->right);
            if (left_height > right_height)
                return {left_height + 1, left_lca};
            if (left_height < right_height)
                return {right_height + 1, right_lca};
            return {left_height + 1, node};
        };
        return dfs(dfs, root).second;
    }
};
