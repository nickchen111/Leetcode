/*
1609. Even Odd Tree
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        if(root == NULL) return true;

        queue<TreeNode*> q;
        q.push(root);
        int depth =  -1;

        while(!q.empty()){
            int sz = q.size();
            vector<int> tmp;
            depth += 1;
            while(sz--){
                TreeNode* node = q.front();
                q.pop();
                if(depth % 2 == 0){
                    if(node->val % 2 == 0) return false;
                }
                else {
                    if(node->val % 2 != 0 ) return false;
                }
                tmp.push_back(node->val);
                
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }

            if(depth % 2 == 0){
                for(int i = 1; i < tmp.size(); i++){
                    if(tmp[i] <= tmp[i-1]) return false;
                }
            }
            else {
                for(int i = 1; i < tmp.size(); i++){
                    if(tmp[i] >= tmp[i-1]) return false;
                }
            }
        }

        return true;
    }  
};

/*
在偶數層的 要是奇數數字 並且遞增
奇數層 偶數數字並且遞減 回傳true or false 樹是否滿足條件
*/
