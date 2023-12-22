/*
958. Check Completeness of a Binary Tree
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {

        queue<TreeNode*> q;
        q.push(root);
        bool flag = 0; // 如果遇到NULL 變成true
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                TreeNode* node = q.front();
                q.pop();
                if(flag == 1 && node != NULL) return false;
                if(node == NULL) flag = 1;
                else {
                    q.push(node->left);
                    q.push(node->right);
                }
            }
        }

        return true;
    }
};

/*
判斷是不是完全二叉樹 
BFS 遍歷點  如果有NULL->flag = 1 後面有正常的點 那就不是完全二叉樹

*/
