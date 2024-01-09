/*
971. Flip Binary Tree To Match Preorder Traversal
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<int> res;
    int i = 0;
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        return DFS(root, voyage) ? res : vector<int>{-1};
    }
    bool DFS(TreeNode* node, vector<int>& voyage){
        if(node == NULL) return true;
        if(i == voyage.size()) return true;
        if(node->val != voyage[i]) return false;
        i++;
        if(node->left && node->left->val != voyage[i]){
            res.push_back(node->val);
            return DFS(node->right, voyage) && DFS(node->left, voyage);
        }
        else{
            return DFS(node->left, voyage) && DFS(node->right, voyage);
        }
    }
};

/*
一個tree 要按照給定的方式做preorder traverse
如果無法滿足 可以將某個tree root翻轉 滿足的話就繼續go(下面的子樹只會連帶被帶過去不會翻轉) 不行return -1
問說最少操作次數下要翻轉哪些node
*/
