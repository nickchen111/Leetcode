/*
700. Search in a Binary Search Tree
*/

//比較慢
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) return nullptr;

        if(root->val == val) return root;
        TreeNode* left = searchBST(root->left, val);
        TreeNode* right = searchBST(root->right, val);
        return left != nullptr ? left:right;
    }
};

/*
解題思維：
二分搜索整棵樹 看有沒有符合的點 tc:o(n) sc:o(lgn)
*/


//比較快的寫法 善用搜索樹
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) return nullptr;

        if(root->val > val){
            return searchBST(root->left, val);
        } 
        else if(root->val < val){
            return searchBST(root->right, val);
        }

        return root;
    }
};

/*
解題思維：
二分搜索整棵樹 看有沒有符合的點 tc:o(n) sc:o(lgn)
但遍歷整棵樹沒有必要因此可以改寫成只遍歷半邊
tc: o(h) sc:o(h) 如果不是傾斜半邊的樹的話兩者皆為lgn
*/
