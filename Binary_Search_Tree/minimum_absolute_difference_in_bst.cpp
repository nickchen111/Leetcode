/*
530. Minimum Absolute Difference in BST
*/


#include <iostream>
#include <cmath>
using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//此題想求在bst中任意兩個node的最小值 特別需要注意兩個位置！ 往左邊後突然往右變大的值 有可能會跟root產生最小值 or 往右變大時突然往左變小的也是一樣 
//所以要用inorder的特性去遍歷tree 搭配preva去記錄先前的node 如此才能兼顧到
//tc: o(n) sc:o(n)
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
