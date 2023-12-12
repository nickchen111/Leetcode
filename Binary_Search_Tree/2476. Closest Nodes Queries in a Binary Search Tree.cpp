/*
2476. Closest Nodes Queries in a Binary Search Tree
*/

//TC:O(n + klgn) k為query次數 SC:O(n)
class Solution {
    vector<int> arr;
public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        
        vector<vector<int>> res;
        DFS(root);
        for(int i = 0; i < queries.size(); i++){
            auto iter = lower_bound(arr.begin(), arr.end(), queries[i]);
            int start, end;
            if(iter == arr.end()){
                end = -1;
                iter = prev(iter,1);
                start = *iter;
                res.push_back({start,end});
            }
            else if(*iter == queries[i]) res.push_back({*iter,*iter});
            else {
                if(iter != arr.begin()) start = *prev(iter);
                else start = -1;
                end = *iter;
                res.push_back({start,end});
            }
        }

        return res;
    }

    void DFS(TreeNode* root){
        if(root == NULL) return;

        DFS(root->left);
        arr.push_back(root->val);
        DFS(root->right);
    }
};
