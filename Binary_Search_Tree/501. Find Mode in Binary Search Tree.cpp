/*
501. Find Mode in Binary Search Tree
*/


// TC:O(n) SC:O(n)
class Solution {
    vector<int> res;
    TreeNode* prev = NULL;
    int count = 0;
    int mxCount = 0;
public:
    vector<int> findMode(TreeNode* root) {
        traverse(root);
        
        return res;
    }

    void traverse(TreeNode* node){
        if (node == nullptr) return;
        
        traverse(node->left);
        //中序遍歷

        //初始化
        if(prev == NULL){
            count = 1;
            mxCount = 1;
            res.push_back(node->val);
        }
        else{
            if(prev->val == node->val){
                count+=1;
                if(count == mxCount){
                    res.push_back(node->val);
                }
                else if(count > mxCount){
                    res.clear();
                    mxCount = count;
                    res.push_back(node->val);
                }
            }
            else if(prev->val != node->val){
                count = 1;
                if(count == mxCount){
                    res.push_back(node->val);
                }
            }
        }
        prev = node;
        traverse(node->right);
    }
};
