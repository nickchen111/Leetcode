/*
1382. Balance a Binary Search Tree
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<int> arr;
public:
    TreeNode* balanceBST(TreeNode* root) {
        //1. get all val from original tree
        getVal(root);
        //2. reconstruct tree
        return construct(0,arr.size()-1);
    }
    void getVal(TreeNode* root){
        if(root == NULL) return;

        getVal(root->left);
        arr.push_back(root->val);
        getVal(root->right);
    }
    TreeNode* construct(int start, int end){
        if(start == end) return new TreeNode(arr[start]);
        if(start > end) return NULL;
        int mid = start + (end - start)/2;
        TreeNode* root = new TreeNode(arr[mid]);
        root->left = construct(start, mid-1);
        root->right = construct(mid+1, end);

        return root;
    }
};

/*
此題考的是一Binary Search Tree 將他轉成 balanced狀態
二叉搜索數
1. 中序遍歷就會是他的數字從小到大... 重新解構？！
2. 有了數組大小隨意找中間值來重構整棵樹
*/
