/*
236. Lowest Common Ancestor of a Binary Tree
*/


// 10/12 計數的方式  TC:O(n) SC:O(lgn)
class Solution {
    TreeNode* res = NULL;
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p || root == q) return root;
        traverse(root, p, q);

        return res;
    }
    //用計數的方式判斷 count = 2代表當前root包含pq count = 1 代表為其中之一
    int traverse(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root== NULL) return 0;
        int left = traverse(root->left, p, q);
        int right = traverse(root->right, p, q);
        int self = (root->val == p->val) ||( root->val == q->val);
        int count = left+right+self;
        //後序遍歷位置 代表第一次更新答案 就會是在最低位置
        if(count == 2 && res == NULL){
            res = root;
        }

        return count;
    }
};
// TC:O(n) SC:O(lgn)
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        return traverse(root, p, q);

    }
     TreeNode* traverse(TreeNode* root, TreeNode* p, TreeNode* q){
         
        //前序位置
        if(root == nullptr) return nullptr;
        if(root == p || root == q) return root;

        TreeNode* left = traverse(root->left, p, q);
        TreeNode* right = traverse(root->right, p, q);

        //後序遍歷位置 會優先找到最低的那個
        if(left != nullptr && right != nullptr){//代表此root兩邊一定都被找到了
            return root;
        }
        if(left == nullptr && right == nullptr){//兩邊都是空
            return nullptr;
        }

        return left == nullptr ? right:left;//其中一邊不為空
    }
};


/*
8/21
解題思維：
此題可以用分解問題的思維去思考
如果一個root 左邊右邊各找到了p q 那此root就是最大共同祖先
如果先找到了某個p or q那麼此點就是答案
如果都找不到就返回nullptr

情况 1，如果 p 和 q 都在以 root 为根的树中，函数返回的即使 p 和 q 的最近公共祖先节点。

情况 2，那如果 p 和 q 都不在以 root 为根的树中怎么办呢？函数理所当然地返回 null 呗。

情况 3，那如果 p 和 q 只有一个存在于 root 为根的树中呢？函数就会返回那个节点。

*/
