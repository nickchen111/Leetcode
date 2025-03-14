/*
2385. Amount of Time for Binary Tree to Be Infected
*/

// 1127
class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {
        // 需要構造一個parent數組
        unordered_map<TreeNode*, TreeNode*> parent;
        TreeNode* sta = nullptr;              
        bool visited[100005] = {false};       
        auto dfs0 = [&](auto &&dfs0, TreeNode* node, TreeNode* prev) {
            if(node == NULL) return;
            if(node -> val == start) sta = node;
            parent[node] = prev;
            dfs0(dfs0, node->left, node);
            dfs0(dfs0, node->right, node);
        }; 
        dfs0(dfs0, root, NULL);
        int res = 0;
        auto dfs = [&](auto &&dfs, TreeNode* node) {
            if(node == NULL || visited[node->val]) return 0;
            visited[node->val] = 1;
            int left = dfs(dfs, node->left);
            int right = right = dfs(dfs, node->right);
            int up = dfs(dfs, parent[node]);
            
            return max({left, right, up})+1;
        };
        return dfs(dfs, sta)-1;
    }
};

// BFS TC:O(n) SC:O(n)
class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {
        map<TreeNode*, TreeNode*> map; // child -> parent 方便我們traverse往前
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* target = NULL;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto node = q.front();
                q.pop();
                if(node->left){
                    q.push(node->left);
                    map[node->left] = node;
                }
                if(node->right){
                    q.push(node->right);
                    map[node->right] = node;
                }
                if(node->val == start) target = node;
            }
        }

        unordered_map<TreeNode*, int> visited;
        q.push(target);

        int res = 0;
        while(!q.empty()){
            int sz = q.size();
            bool flag = 0;
            while(sz--){
                auto node = q.front();
                q.pop();
                if(visited[node]) continue;
                visited[node] = 1;
                if(node -> left && visited[node->left] != 1){
                    q.push(node->left);
                    flag = 1;
                }
                if(node -> right && visited[node->right] != 1){
                    q.push(node->right);
                    flag = 1;
                }
                if(map[node] && visited[map[node]] != 1){
                    q.push(map[node]);
                    flag = 1;
                }
            }
            if(flag) res++;
        }

        return res;

    }
};

// DFS TC:O(n) SC:O(n)
class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {
        //轉成int型態的graph
        unordered_map<int, vector<int>> graph;
        traverseToGraph(graph, root);
        
        vector<bool> visited(1e5+1,0);
        return DFS(start, graph, visited)-1;
    }
    void traverseToGraph(unordered_map<int, vector<int>>& graph, TreeNode* node){
        if(node == NULL) return;
        if(node->left){
            graph[node->val].push_back(node->left->val);
            graph[node->left->val].push_back(node->val);
            traverseToGraph(graph, node->left);
        }
        if(node->right){
            graph[node->val].push_back(node->right->val);
            graph[node->right->val].push_back(node->val);
            traverseToGraph(graph, node->right);
        }
    }
    int DFS(int node, unordered_map<int, vector<int>>& graph,vector<bool>& visited){
        visited[node] = 1;
        int res= 0;
        for(auto &x : graph[node]){
            if(!visited[x])
                res = max(res, DFS(x, graph, visited));
        }

        return res + 1;
    }
};
