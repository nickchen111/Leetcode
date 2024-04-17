/*
988. Smallest String Starting From Leaf
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<string> arr;
public:
    string smallestFromLeaf(TreeNode* root) {
        if(root == NULL) return "";
        string tmp;
        
        DFS(root, tmp);
        string res;
        for(int i = 0; i < arr.size(); i++){
            if(res.empty() || res > arr[i]){
                res = arr[i];
            }
        }

        return res;
    }
    void DFS(TreeNode* node, string tmp){
        if(node->left == NULL && node->right == NULL){
            tmp += node->val+'a';
            reverse(tmp.begin(), tmp.end());
            arr.push_back(tmp);
            return;
        }
        char ch = node->val+'a';
        if(node->left) DFS(node->left, tmp + ch);
        if(node->right) DFS(node->right, tmp+ch);

    }
};

// 從leaf到root 字典序最小的字串
