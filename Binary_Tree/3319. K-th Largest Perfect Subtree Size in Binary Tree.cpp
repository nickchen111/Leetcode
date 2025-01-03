/*
3319. K-th Largest Perfect Subtree Size in Binary Tree
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */


// TC:O(n) SC:O(n) quick select 去找第k大的數字 完全是線性了
class Solution {
    vector<int> arr;
    static bool greater(int a, int b) {
        return a > b;
    }
public:
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        DFS(root);
        
        if(k-1 < arr.size()) {
            std::nth_element(arr.begin(), arr.begin() + k - 1, arr.end(), greater);
            return (1 << arr[k-1]) - 1;
        }
        else return -1;
    }

    int DFS(TreeNode* root) {
        if(root == nullptr) return 0;
        int left = DFS(root->left); // subtree, nodeNumber
        int right = DFS(root->right);
        if(left == -1 || right == -1) return -1;
        if(left != right) return -1;

        arr.push_back(left + 1);
        return left + 1;
    }
};


// TC:O(n + mlgm) m為是完全二叉樹的節點數量 SC:O(n + m)
class Solution {
    vector<int> arr;
public:
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        DFS(root);
        sort(arr.rbegin(), arr.rend());
        
        if(k-1 < arr.size()) return ((1 << arr[k-1])) - 1;
        else return -1;
        
    }
    int DFS(TreeNode* root) {
        if(root == NULL) return 0;
        int left = DFS(root -> left); // subtree, nodeNumber
        int right = DFS(root -> right);
        if(left == -1 || right == -1) return -1;
        if(left != right) return -1;

        arr.push_back(left+1);
        return left+1;
    }
};

// TC:O(n + mlgm) m為是完全二叉樹的節點數量 SC:O(n + m)
class Solution {
    vector<int> arr;
public:
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        DFS(root);
        sort(arr.rbegin(), arr.rend());
        
        if(k-1 < arr.size()) return arr[k-1];
        else return -1;
        
    }
    vector<int> DFS(TreeNode* root) {
        if(root == NULL) return {1,0};
        vector<int> left = DFS(root -> left); // subtree, nodeNumber
        vector<int> right = DFS(root -> right);
        
        if(left[0] == 1 && right[0] == 1 && left[1] == right[1]) {
            arr.push_back(left[1]*2 + 1);
            return {1, left[1]*2 + 1};
        }
        
        return {0,0};
    }
};
