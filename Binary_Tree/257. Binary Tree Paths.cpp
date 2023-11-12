/*
257. Binary Tree Paths
*/

// DFS Backtrack TC:(n) SC:O(n)
lass Solution {
    vector<string> res;
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        //DFS
        
        DFS(root,"");

        return res;
    }
    void DFS(TreeNode* root, string tmp){
        if(root == NULL) return;
        if(root->left == NULL && root->right == NULL){
            tmp+=to_string(root->val);
            
            res.push_back(tmp);
            return;
        }
        
        DFS(root->left,tmp+to_string(root->val)+"->");
        DFS(root->right,tmp+to_string(root->val)+"->");
    }
};

// 紀錄路徑的寫法
class Solution {
    vector<string> res;
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        //DFS
        vector<string> tmp;
        DFS(root,tmp);

        return res;
    }
    void DFS(TreeNode* root, vector<string>& tmp){
        if(root == NULL) return;
        if(root->left == NULL && root->right == NULL){
            tmp.push_back(to_string(root->val));
            string str = "";
            for(int i = 0; i<tmp.size(); i++){
                if(i == tmp.size()-1) str+=tmp[i];
                else{
                    str+=tmp[i]+"->";
                }
            }
            res.push_back(str);
            tmp.pop_back();
            return;
        }
        
        
        tmp.push_back(to_string(root->val));
        DFS(root->left,tmp);
        DFS(root->right,tmp);
        tmp.pop_back();
    }
};
