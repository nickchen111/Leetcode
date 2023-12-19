/*
987. Vertical Order Traversal of a Binary Tree
*/

// TC:O(n) SC:O(n)
class Solution {
    map<int, multiset<pair<int,int>>> map; // col -> row, val
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        DFS(root,0,0);
        vector<vector<int>> res;
        // 目標是按照col 由小到大 裡面的數值
        int idx = -1;
        for(auto p : map){
            res.push_back({});
            idx += 1;
            for(auto t : p.second){
                res[idx].push_back(t.second);
            }
        }

        return res;
    }

    void DFS(TreeNode* root, int row, int col){
        if(root == NULL) return;
        map[col].insert({row,root->val});
        DFS(root->left,row+1, col-1);
        DFS(root->right,row+1, col+1);
    }
};

/*
此題就是想要將col由小到大排出row也是由小到大排序每一個相同col中 row 如果相同要按照大小sort
*/
