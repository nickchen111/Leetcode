/*
2641. Cousins in Binary Tree II
*/

// BFS TC:O(n) SC:O(w) 直接在當前一層就開始擷取下一層的訊息
class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        if(root == NULL) return NULL;
        root->val = 0;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int sz = q.size();
            int sum = 0;
            vector<TreeNode*> temp;
            while(sz--){
                TreeNode* node = q.front();
                q.pop();
                temp.push_back(node);
                if(node->left) {
                    sum += node->left->val;
                    q.push(node->left);
                }
                if(node->right){
                    sum += node->right->val;
                    q.push(node->right);
                }
            }

            for(auto node : temp){
                int t = sum;
                if(node->left) t -= node->left->val;
                if(node->right) t -= node->right->val;
                if(node->left) node->left->val = t;
                if(node->right) node->right->val = t;
            }
        }

        return root;
    }
};

// Myself DFS + BFS TC:O(2*n) SC:O(2*n + w)
class Solution {
    using LL = long long;
    unordered_map<int, unordered_map<TreeNode*, LL>> depth2ParentSum; //. depth -> parent, sum
    vector<LL> depth;
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        if(root == NULL) return NULL;

        queue<pair<TreeNode*, TreeNode*>> q; //< node, its parent>
        TreeNode* parent = new TreeNode(-1);
        q.push({root, parent});
        int step = 0;
        while(!q.empty()){
            int sz = q.size();
            LL totalDepthSum = 0;
            depth.push_back({});
            
            while(sz--){
                auto node = q.front();
                q.pop();
                totalDepthSum += node.first->val;
                depth2ParentSum[step][node.second] += node.first->val;
                if(node.first->left) q.push({node.first->left,node.first});
                if(node.first->right) q.push({node.first->right,node.first});
            }
            depth[step] = totalDepthSum; 
            step += 1;
        }

        DFS(root,0, parent);

        return root;
    }
    void DFS(TreeNode* node, int step, TreeNode* parent){
        if(node == NULL) return;
        // totalLayerSum - totalParentSum
        DFS(node->left, step+1, node);
        DFS(node->right, step+1, node);
        node->val = depth[step] - depth2ParentSum[step][parent];
    }
};

/*
此題想將相同層上的節點改成跟他同層但是不同parent的總和      
開個數組紀錄每一層由哪些parent底下可以組成的總和 
depth -> parent -> parentSum;
totalLayerSum - totalParentSum; -> vector<LL> depth;//每一層的sum
此方法需要BFS + DFS 遍歷兩次
另一個更簡單的想法可以直接用一個BFS搞定 只要在當前數組時就開始為他的孩子著想 當第n層就開始計算第n+1層的結果 
*/
