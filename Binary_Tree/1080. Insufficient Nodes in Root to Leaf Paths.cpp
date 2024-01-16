/*
1080. Insufficient Nodes in Root to Leaf Paths
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        if(root == NULL) return NULL;
        bool res = DFS(root, limit, 0);

        return res == false ? NULL : root;
    }
    bool DFS(TreeNode* node, int limit, int sum){
        if(node->left == NULL && node->right == NULL){
            sum += node->val;
            if(sum < limit) return false;
            return true;
        }

        bool left = false;
        bool right = false;
        if(node->left){
            left = DFS(node->left, limit, sum + node->val);
        }
        if(node->right){
            right = DFS(node->right, limit, sum + node->val);
        }

        if(!left && !right) return false;
        if(!left) node->left = NULL;
        if(!right) node->right = NULL;

        return true;
    }
};

/*
刪除從root到此題所謂的leaf節點 如果某個節點他整條path下來sum < limit 如果左右兩邊都不行 那他就要刪掉
這題最棒的想法就是去思考站在某一點上如果左邊右邊都不行 那自己本身也是需要刪除的點 這時就要回傳個什麼給上一個節點告知她我也是需要被刪除的點
如果左右只有某一個點是要被刪除的 那麼就單獨將左右節點設為NULL
*/
