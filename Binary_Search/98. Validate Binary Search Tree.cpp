/*
98. Validate Binary Search Tree
*/

// 10/13 TC:O(n) SC:O(h)h平均是logn 最慘為n
class Solution {
    //這感覺跟1438題一樣就是個帶球比大小的題目
public:
    bool isValidBST(TreeNode* root) {
        return traverse(root,LLONG_MIN,LLONG_MAX);
    }

    bool traverse(TreeNode* root, long min_val, long max_val){
        if(root == NULL) return true;
        if(root->val >= max_val || root->val <= min_val) return false;
       

        return traverse(root->left, min_val, root->val) && traverse(root->right, root->val, max_val);
    }
};



//la大寫法
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValid(root, nullptr, nullptr);
    }
    bool isValid(TreeNode* root, TreeNode* min, TreeNode* max){
        if(root == nullptr) return true;

        if(min != nullptr && root->val <= min->val) return false;
        if(max != nullptr && root->val >= max->val) return false;

        return isValid(root->left, min, root) && isValid(root->right,root, max);
    }
};


/*
解題思路：
root 的整个左子树都要小于 root.val，整个右子树都要大于 root.val。
我们通过使用辅助函数，增加函数参数列表，在参数中携带额外信息，将这种约束传递给子树的所有节点，这也是二叉树算法的一个小技巧

tc: o(n)
sc:o(h) h平均是logn 最慘為n
*/


//之前自己的寫法
class Solution {
//dfs
public:
    bool isValidBST(TreeNode* root) {
        return isValid(root, LLONG_MAX, LLONG_MIN);

    }
    bool isValid(TreeNode* root, long max_val, long min_val){
        if(!root) return true; //找不到了 代表符合bst
        if(root->val >= max_val || root->val <= min_val) return false;
        return isValid(root->left, root->val, min_val) && isValid(root->right, max_val, root->val);//兩個都是true才會返回true 
    }
};
