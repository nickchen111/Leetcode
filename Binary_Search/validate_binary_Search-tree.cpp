/*
98. Validate Binary Search Tree
Given the root of a binary tree, determine if it is a valid binary search tree (BST).
A valid BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
Input: root = [2,1,3]
Output: true

Example 2:
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.

Constraints:
The number of nodes in the tree is in the range [1, 104].
-2＾31 <= Node.val <= 2＾31 - 1  這裡的限制導致要用long 才能在判斷式中不會被判為false 如果剛好node val 為int上限值的話
*/



#include <iostream>
#include <climits>
using namespace std; 
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


//此題是想求一個root左邊的數字都不能超過root 且也不能大於subtree的root 只有subtree右邊可以超過 但也不能大於主root
//右邊的數字都要大於root 右邊subtree root的數字不能超過suntree root但要大於主root

//所以我的邏輯寫出來的沒顧慮到主root大小跟subtree root分之出來的node關係 才導致測資沒過 在root = {5 4 6 null null 3 7}不過
//這是我的思考邏輯結合chatgpt寫出來的
class Solution {
//dfs
public:
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) return true;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        bool ans = isValid(root, left, right);

        return ans;

    }
    bool isValid(TreeNode* root, TreeNode* left, TreeNode* right){
        if(left && left->val >= root->val) return false;
        if(right && right->val <= root->val) return false;

        bool isvalidleft =(left) ? isValid(left, left->left,left->right):true; //這裡用bool的寫法來判斷true false 很高端 可學起來
        bool isvalidright =(right) ? isValid(right, right->left,right->right):true;

        return isvalidleft && isvalidright;
    }
};

//此題也可以用inorder的方式去做比較
//正確邏輯解釋一開始是用long的最大值最小值範圍 然後用root當左邊最大值右邊最小值慢慢去遞迴
class Solution1 {
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

/*
时间复杂度：
在每个节点上只进行了一次递归调用，因此递归的时间复杂度为 O(N)，其中 N 是二叉搜索树中的节点数。
空间复杂度：
递归的空间复杂度取决于递归调用的深度，而在这个解法中，递归的深度等于二叉搜索树的高度。最坏情况下，
二叉搜索树可能退化成链式结构，高度为 N，因此递归的空间复杂度为 O(N)。而在平衡二叉搜索树的情况下，递归的空间复杂度为 O(logN)。
*/