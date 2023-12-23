/*
979. Distribute Coins in Binary Tree
*/

// TC:O(n) SC:O(n)
class Solution {
    int res = 0;
public:
    int distributeCoins(TreeNode* root) {
        DFS(root);

        return res;
    }
    int DFS(TreeNode* root){
        if(root == NULL) return 0;
        int leftNeed = DFS(root->left);
        int rightNeed = DFS(root->right);
        res += abs(leftNeed) + abs(rightNeed);

        return leftNeed + rightNeed + root->val - 1;
    }
};

/*
此題要你移動節點上的硬幣 可以從parent到child 或著反過來
問說要移動到每個點硬幣數量一樣 最少需要移動幾次
如果每個有硬幣的點大於2的就會是要移動的對象 找個最近的空的宜過去
將他遍歷完轉成數組 ->無法正確標示出每個點的距離差
用分治思想 每個點他們缺或是多東西都會傳給他的上層 他的上層做一些計算 去消化這些資訊再決定要傳給上層多
*/
