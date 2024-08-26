/*
590. N-ary Tree Postorder Traversal
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<int> res;
public:
    vector<int> postorder(Node* root) {
        DFS(root);

        return res;
    }
    void DFS(Node* root){
        if(root == NULL) return;

        for(auto ch : root->children){
            DFS(ch);
        }

        res.push_back(root->val);
    }
};
