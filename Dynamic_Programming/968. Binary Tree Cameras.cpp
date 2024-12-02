/*
968. Binary Tree Cameras
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minCameraCover(TreeNode* root) {
       
        auto dfs = [&](auto &&dfs, TreeNode* node) -> vector<int> {
            if(node == NULL) return {INT_MAX/2, 0, 0};
            auto left = dfs(dfs, node->left);
            auto right = dfs(dfs, node->right);
            int num1 = 1 + min({left[0],left[1], left[2]}) + min({right[0],right[1], right[2]});
            int num2 = min(left[0], left[2]) + min(right[0], right[2]);
            // int num3 = min({left[0] + right[2], left[2] + right[0], left[0] + right[0]});
            int num3 = min(left[0], left[2]) + min(right[0], right[2]) + max(0, min(left[0] - left[2], right[0] - right[2]));
            return {num1, num2, num3};
        };

        auto res = dfs(dfs, root);
        return min(res[0], res[2]);
    }
};

/*
cameras可以監控當下點，父節點，子節點
每個節點就是兩種選擇 放or不放 放了 後面孩子是否要放?! 取決於孩子後面的節點數量
三種狀況
1. 選了的話 後面可以是不選但是下面有人罩他 + 不選且下面沒人罩他
2. 不選期望上面罩我 = 下面的不選
3. 不選且下面有人罩我 = 下面選 or 下面不選但有人罩
*/
