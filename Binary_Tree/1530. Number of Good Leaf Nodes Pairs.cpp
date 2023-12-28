/*
1530. Number of Good Leaf Nodes Pairs
*/

// TC:O(n^2*k) k 為每次BFS會加入的節點數量 SC:O(n)  
class Solution {
    int res = 0;
    unordered_map<TreeNode*, int> leaf;
public:
    int countPairs(TreeNode* root, int distance) {
        // find leafnode and construct graph
        unordered_map<TreeNode*, vector<TreeNode*>> graph; // child -> parent
        DFS(root, graph);
        for(auto s : leaf){
            traverse(graph,s.first, distance);
        }

        return res/2;

    }
    void DFS(TreeNode* node, unordered_map<TreeNode*, vector<TreeNode*>>& graph){
        if(node == NULL) return;
        if(node->left == NULL && node->right == NULL){
            leaf[node] = 1;
        }
        
        if(node->left){
            graph[node].push_back(node->left);
            graph[node->left].push_back(node);
        }
        if(node->right){
            graph[node].push_back(node->right);
            graph[node->right].push_back(node);
        }
        DFS(node->left, graph);
        DFS(node->right, graph);
    }
    void traverse(unordered_map<TreeNode*, vector<TreeNode*>>& graph, TreeNode* cur, int distance){
        
        queue<pair<TreeNode*,int>> q;
        q.push({cur,0});
        
        unordered_set<TreeNode*> set;
        while(!q.empty()){
            int sz = q.size();
            bool flag = 0;
            while(sz--){
                TreeNode* node = q.front().first;
                int step = q.front().second;
                q.pop();
                if(set.find(node) != set.end()) continue;
                set.insert(node);
                if(leaf[node] && node != cur && step <= distance) res += 1;
                if(step > distance) {
                    flag = 1;
                    break;
                }
                for(auto neighbor : graph[node]){
                    q.push({neighbor,step + 1});
                }
            }
            if(flag) break;
        }
    }
};

/*
leaf node 之間的距離 小於等於distance 就紀錄起來
正著想挺難的 要想紀錄每個點到可以貢獻出最短距離的路徑 反著想從leaf node出發看可以走多少步
*/
