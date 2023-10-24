/*
543. Diameter of Binary Tree
*/


class Solution {
    int maxdiameter = 0;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDepth(root);
        
        return maxdiameter;
    }
    int maxDepth(TreeNode* root){
        if(root == nullptr) return 0;

        int leftmax = maxDepth(root->left);
        int rightmax =  maxDepth(root->right);
        maxdiameter = max(maxdiameter, leftmax+rightmax);//放在後序位置 才能得知left right最大值
        //也就是說在這裡root做兩件事 1.把自己當root看最大多長 把自己當拐點只是某個點的左邊或右邊

        return 1+max(leftmax, rightmax);//只是左邊或右邊
    }
};

/*
解題思路
用分解問題的方式求左跟右的最長長度
很巧妙地要用後序遍歷可以獲取子樹訊息的方式來獲取最大長度
在分解過程 每個root都有兩個任務 1.把自己當root看最大多長 把自己當拐點只是某個點的左邊或右邊
tc: o(n) sc: o(n)
*/
