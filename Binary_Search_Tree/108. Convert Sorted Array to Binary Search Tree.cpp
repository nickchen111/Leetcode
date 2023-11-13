/*
108. Convert Sorted Array to Binary Search Tree
*/

// Divide and Conquer TC: O(nlgn) SC:O(n)
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        //inorder 
       
        return DivideAndConquer(nums,0,nums.size()-1);
    }
    TreeNode* DivideAndConquer(vector<int>& nums, int left, int right){
        if(left > right) return NULL;
        if(left == right) return new TreeNode(nums[left]);

        int mid = left+(right-left)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = DivideAndConquer(nums,left,mid-1);
        root->right = DivideAndConquer(nums,mid+1,right);
        return root;
    }
};
