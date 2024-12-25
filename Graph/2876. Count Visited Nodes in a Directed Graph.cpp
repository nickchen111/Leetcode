/*
2876. Count Visited Nodes in a Directed Graph
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();
        vector<int> indegree(n);
        vector<vector<int>> redges(n);
        // 建立入度資訊與reverse edges
        for(int x = 0; x < n; x++) {
            int y = edges[x];
            indegree[y] += 1;
            redges[y].push_back(x);
        }
        queue<int> q;
        for(int x = 0; x < n; x++) {
            if(indegree[x] == 0) q.push(x);
        }
        // 刪除非基環的節點入度
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                int node = q.front();
                q.pop();
                int nxt = edges[node];
                indegree[nxt] -= 1;
                if(indegree[nxt] == 0) q.push(nxt);
                
            }
        }
        vector<int> res(n);
        // reverse dfs 去判斷每個樹枝的depth
        auto rdfs = [&](auto &&rdfs, int x, int depth) -> void {
            res[x] = depth;
            for(int y : redges[x]){
                if(indegree[y] == 0) {
                    rdfs(rdfs, y, depth+1);
                }
            }
        };

        for(int i = 0; i < n; i++) {
            if(indegree[i] <= 0) continue; // 防止重複遍歷基環節點
            vector<int> ring;
            for(int x = i;; x = edges[x]) {
                ring.push_back(x);
                indegree[x] = -1;
                if(edges[x] == i) break;
            }
            for(int x : ring){
                rdfs(rdfs, x, ring.size());
            }
        }

        return res;
 
    }
};
