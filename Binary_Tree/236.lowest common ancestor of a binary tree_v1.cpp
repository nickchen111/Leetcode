/*
236. Lowest Common Ancestor of a Binary Tree
*/


#include <iostream>
#include <vector>
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

//想不出來 這題跟之前做過的dfs套路不太一樣 所以想的邏輯還是挺重要的 不能單靠模板
//此題思考方向在於 將root分兩邊去dfs 如果兩邊到最後都可以找得到（都不是nullptr被return root
//但如果是左邊的先被找到or右邊 那一個地方會先返回 left or right的結果
//大方向還是在於兩個一起找到返回root 先找到一個就返回單一個這樣的一個概念
//ex:假設在左邊subtree中先返回到了一個左邊 那他的左邊即不是空 右邊回來時他的右邊也不是空 就返回一個root, 但他再繼續返回到中間時他就會變成是中間的left 所以最終會是left為答案


//dfs tc: o(n) sc:o(n) dfs遞迴肯定會開一個stack去做
class Solution {
//dfs
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr || root == p || root == q) //邊界條件
        return root;
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p ,q);

        if(left != nullptr && right != nullptr) return root; //必定是最高的那個 才有可能同時兼容兩者（這邊指的最高也有可能是tree底下subtree中最高看是在哪一層）
        if(left != nullptr) return left;
        else return right;
    }
};

