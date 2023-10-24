/*
450. Delete Node in a BST
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
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return nullptr;//base case

        if(root->val == key){
            if(root->left == nullptr) return root->right;
            else if(root->right == nullptr) return root->left;

            TreeNode* minNode = getMin(root->right);//去尋找右子樹的最小值
            root->right = deleteNode(root->right, minNode->val);//把右子樹那個最小點刪掉
            //開始把改動後的結果build up起來
            minNode->left = root->left;
            minNode->right = root->right;
            root = minNode;
        }

        else if(root->val > key){
            root->left = deleteNode(root->left, key);
        }

        else if(root->val < key){
            root->right = deleteNode(root->right, key);
        }

        return root;//沒做任何事就乖乖把自己return 回去 or 做完事的node也從這裡return

    }
    TreeNode* getMin(TreeNode* node){
        while(node->left != nullptr) node = node ->left;
        return node;
    }
};

/*
解題思維：
bst的思路去擴充此題程式碼 首先一樣是找 以及預設base case
delete主要三動作
1.找到以後先判斷是否後面沒接node or 只接單一節點 or 接了兩個節點
2.如果是最後一種情況 就去找右子樹最小值 or左子樹最大值去取代他 取代前先用一個node 當作容器去接他
3.接著把此node刪除 因為已經有個node接到他的值了 可以放心刪除 最後把所有改動build up起來

tc: o(h) sc: o(h)
*/
