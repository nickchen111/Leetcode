/*
1008. Construct Binary Search Tree from Preorder Traversal
*/

//設定範圍構造 TC:O(nlgn) SC:O(lgn)
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int n = preorder.size();
        if(n == 0) return NULL;

        return construct(preorder, 0, n-1);
    }
    TreeNode* construct(vector<int>& preorder, int start, int end){
        if(start > end) return NULL;
        if(start == end) return new TreeNode(preorder[start]);

        TreeNode* root = new TreeNode(preorder[start]);
        int i = start + 1;
        while (i <= end && preorder[i] < preorder[start]) {
            i++;
        }

        root -> left = construct(preorder, start + 1, i - 1);
        root -> right = construct(preorder, i, end);
        return root;
    }
};

// 開新空間構造
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int n = preorder.size();
        if(n == 0) return NULL;
        if(n == 1) return new TreeNode(preorder[0]);
        TreeNode* root = new TreeNode(preorder[0]);

        vector<int> left;
        vector<int> right;
        for(int i = 1; i < n; i++){
            if(preorder[i] < preorder[0]){
                left.push_back(preorder[i]);
            } 
            else right.push_back(preorder[i]);
        }
        
        root -> left = bstFromPreorder(left);
        root -> right = bstFromPreorder(right);

        return root;
    }
};


/*
此題給你一preorder遍歷的vector數組
要你構造BST 構造樹顯然是用遞迴
preorder: root -> left -> right
要注意BST限制 左邊界右邊界的方式去構造
*/
