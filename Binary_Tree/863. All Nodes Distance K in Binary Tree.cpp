/*
863. All Nodes Distance K in Binary Tree
*/

// DFS 拐點TC:O(n) SC:O(n)
class Solution {
    vector<int> res;
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {

        DFS(root,target,k);

        return res;
    }

    int DFS(TreeNode* node, TreeNode* target, int k){
        if(node == NULL) return -1;
        //如果一路找到target 按照自己定義的要求那麼target離子節點距離為0
        if(node == target){
            fetch(node, k);//這一步以自己target繼續往後走k
            return 0;
        }

        int depth1 = DFS(node->left, target, k);
        //說明在我左邊沒錯
        if(depth1 != -1){
            if(depth1 == k - 1){
                res.push_back(node->val);
            }
            //將他當成拐點要走去右邊可以剩下的step
            else{
                fetch(node->right, k - depth1 - 2);
            }

            return depth1 + 1;
        }
        int depth2 = DFS(node->right, target, k);
        if(depth2 != -1){
            if(depth2 == k - 1){
                res.push_back(node->val);
            }
            //將他當成拐點要走去右邊可以剩下的step
            else{
                fetch(node->left, k - depth2 - 2);
            }

            return depth2 + 1;
        }

        return -1;
    }

    void fetch(TreeNode* node, int k){
        if(node == NULL) return;
        if(k == 0) {
            res.push_back(node->val);
            return;
        }
        if(k < 0) return;

        fetch(node->left, k-1);
        fetch(node->right,k-1);
    }
};

// BFS TC:O(n) SC:O(2*n)
class Solution {
    vector<vector<int>> graph;
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if(root == NULL) return {};
        if(k == 0) return {target->val};
        graph.resize(502);
        DFS(root->left, root->val);
        DFS(root->right,root->val);

        queue<int> q;
        q.push(target->val);

        int count = 0;
        vector<bool> visited(501);
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int cur = q.front();
                q.pop();
                if(visited[cur]) continue;
                visited[cur] = 1;
                for(auto neighbor : graph[cur]){
                    if(visited[neighbor]) continue;
                    q.push(neighbor);
                }
            }
            count += 1;
            if(count == k) break;
        }

        vector<int> res;
        while(!q.empty()){
            res.push_back(q.front());
            q.pop();
        }

        return res;
    }

    void DFS(TreeNode* root, int cur){
        if(root == NULL) return;
        graph[cur].push_back(root->val);
        graph[root->val].push_back(cur);
        DFS(root->left, root->val);
        DFS(root->right, root->val);
    }
};


/*
求出以某個node為出發點 走k步可以到的node有哪些
1. 將tree轉成做BFS無向圖 好做超級多 但是佔空間
2. 如果要用構造的方式算距離 DFS的話 不佔空間 速度一樣:
將每個點都當成拐點 去看他是否跟target在同一棵樹上 看他左邊找不找得到 右邊呢 肯定有一個找不到
寫成判斷他左邊的點跟target 距離多遠然後就可以做兩件事 一件事自己為拐點去看另一側的能不能走到 
另一件事將自己距離此target距離傳回
*/
