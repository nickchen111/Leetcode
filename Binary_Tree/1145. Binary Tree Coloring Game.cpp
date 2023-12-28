/*
1145. Binary Tree Coloring Game
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        DFS(root,x);
        int p =  n - (1 + leftMax + rightMax); 
        return max(p, max(leftMax,rightMax)) > n/2;
    }
    //怕紅色選頭 要截斷任何一邊
    int leftMax;
    int rightMax;
    int DFS(TreeNode* root, int x){
        if(root == NULL) return 0;
        int left = DFS(root->left,x);
        int right = DFS(root->right,x);
        if(root->val == x){
            leftMax = left;
            rightMax = right;
           
        }
        return 1 + left + right;
    }
};

/*
題目描述複雜但其實就是 後手看先手獲得了多少節點 所有節點減去他獲得節點數 /2 看有沒有過半
或者說去搶他的左右節點其中一個
*/
