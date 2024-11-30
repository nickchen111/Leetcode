/*
337. House Robber III
*/

// 1130 
class Solution {
public:
    int rob(TreeNode* root) {
        int res = 0;
        auto dfs = [&](auto &&dfs, TreeNode* node) -> pair<int,int> {
            if(node == NULL) return {0,0};
            auto [sub_rob1, sub_norob1] = dfs(dfs, node-> left);
            auto [sub_rob2, sub_norob2] = dfs(dfs, node-> right);
            int rob = node->val + sub_norob1 + sub_norob2;
            int norob = max(sub_rob1, sub_norob1) + max(sub_rob2, sub_norob2);
            res = max({res, rob, norob});
            return {rob, norob};
        };
        dfs(dfs, root);
        return res;
    }
};

//recursion 可用memo優化 或者直接數組優化 ->TLE
//TC:O(n) SC:O(n)
class Solution {
public:
    int rob(TreeNode* root) {
        return DFS(root, 1);
    }

    int DFS(TreeNode* node, int flag){// flag = 1: can choose, flag = 0: can not choose
        if(node == NULL) return 0;

        if(flag == 0){
            return DFS(node->left,1)+DFS(node->right,1);
        }

        else {
            int option1 = node->val + DFS(node->left, 0) + DFS(node->right, 0);
            int option2 = DFS(node->left,1)+DFS(node->right,1);
            return max(option1, option2);
        }

    }
};

//優化 直接用數組代表可搶可不搶
//TC:O(n) SC:O(n)
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> nums = DFS(root);

        return max(nums[0], nums[1]);
    }

    vector<int> DFS(TreeNode* node){
        if(node == NULL) return {0,0};

        vector<int> left = DFS(node->left);
        vector<int> right = DFS(node->right);

        vector<int> res(2);

        res[0] = left[1]+right[1]+node->val;//我這個節點搶了 下面的就不能搶
        res[1] = max(left[1], left[0])+max(right[1], right[0]);//我這個節點不搶 下面可搶可不搶 取最大

        return res;
    }
};
