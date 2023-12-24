/*
1372. Longest ZigZag Path in a Binary Tree
*/

// TC:O(n) SC:O(n)
class Solution {
    int res = 0;
public:
    int longestZigZag(TreeNode* root) {
        DFS(root, 1); // 1 represent left
        DFS(root, -1);// -1 represent right
        //計算的是節點數量 要再減一
        return res-1;
    }

    int DFS(TreeNode* node, int prev){
        if(node == NULL) return 0;
        
        if(prev == 1){
            int right = DFS(node->right,-1);
            res = max(res, 1 + right);
            DFS(node->left, -1);
            
            return 1 + right;
        }
        else {
            int left = DFS(node->left, 1);
            res = max(res, 1 + left);
            //以下面的點作為起點繼續走看看 不能讓下面的點走一個-1 之後的點往左 會跟原本方向重複 TLE
            DFS(node->right, 1);
            

            return 1 + left;
        }
        
    }
};

/*
想找出一棵樹中哪個之字走法長度最長
number of node - 1
此題難點在於要思考當前的點照著之字走 但也可以讓下一個點為起頭並且往另一個方向繼續探索
*/
