/*
114. Flatten Binary Tree to Linked List
*/


class Solution {
public:
    void flatten(TreeNode* root) {
        if(root == nullptr) return;

        flatten(root->left);
        flatten(root->right);
        //拉平完在開始做動作

        //1.左右子樹已經拉好了
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        //2. 將root左邊架空 並在右邊接上拉平的左子樹在接上右子樹
        root->left = nullptr;
        root->right = left;

        TreeNode* p = root;
        while(p->right != nullptr){
            p = p->right;
        }
        p->right = right;
    }
};
/*
解題思維
此題想將一棵樹的左邊全部放到右邊去 順序要是前序遍歷
如果能用traverse就會很簡單 但因為題目是void函式 不能有返回值需原地修改
所以改用分解問題的思維模式
1.想創建一個函式他可以拉平flaten一顆子樹
2.那麼我們就可先把左子樹根右子樹都拉平 然後將root的右邊先接上左子樹最後接上右子樹
*/
