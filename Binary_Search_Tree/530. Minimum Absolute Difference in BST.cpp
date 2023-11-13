/*
530. Minimum Absolute Difference in BST
*/


//TC: o(n) SC:o(h)
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        traverse(root);
        return ans;
    }
    TreeNode* prev = nullptr;
    int ans = INT_MAX;//放在global 大家都可任意變動數值

    void traverse(TreeNode* root){
        if(root == nullptr) return;
        traverse(root->left);

        //inorder遍歷的位置
        if(prev != nullptr){
            ans = min(ans, root->val - prev->val);
        }
        prev = root;
        traverse(root->right);
    }
};

/*
解題思路
利用inorder 的方式自然而然的排序出這棵樹由小而大
且bst有個重要的特性 左邊所有點必定小於根節點 右邊所以點必定大於根節點
*/
