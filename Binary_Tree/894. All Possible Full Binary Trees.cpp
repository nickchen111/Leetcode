/*
894. All Possible Full Binary Trees
*/

// TC:O(2^n) SC:O(n) 每個節點可能都要遞迴調用 2*2*2... n次 
class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        if(n % 2 == 0) return {};
        if(n == 1){
            TreeNode* node = new TreeNode(0);
            return {node};
        }

        vector<TreeNode*> res;

        for(int i = 2; i < n; i++){
            if(i-1 % 2 == 0 || (n-i) % 2 == 0) continue;
            
            vector<TreeNode*> left = allPossibleFBT(i-1);
            vector<TreeNode*> right = allPossibleFBT(n-i);
            for(auto l : left){
                for(auto r : right){
                    TreeNode* root = new TreeNode(0);
                    root ->left = l;
                    root -> right = r;
                    res.push_back(root);
                }
            }
        }

        return res;
    }
};

/*
用n個節點構造出 full binary tree 每個節點不是沒有children 就是有兩個children
選擇某一個節點當root 左右的數量絕對要是奇數
如果n = 8 -> -1剩7 3 4 fail 
n = 4 -> fail 所以偶數個節點fail 
接下來就是有點Divede and conquer 的味道 思考該怎麼分
1 2 3 4 5 6 7 只有中間五種可以當root
*/
