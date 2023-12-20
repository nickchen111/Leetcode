/*
2492. Minimum Score of a Path Between Two Cities
*/

// Union_Find TC:O(E) SC:O(V)
class Solution {
    class UF{
        vector<int> parent;
    public:
        UF(int n){
            for(int i = 0; i < n; i++){
                parent.push_back(i);
            }
        }
        int find(int x){
            if(x != parent[x]){
                parent[x] = find(parent[x]);
            }

            return parent[x];
        }

        void union_(int x,int y){
            x = find(x);
            y = find(y);
            if(x > y){
                parent[x] = y;
            }
            else parent[y] = x;
        }
    };
public:
    int minScore(int n, vector<vector<int>>& roads) {

        UF uf(n+1);
        for(auto road : roads){
            int node1 = road[0], node2 = road[1];
            if(uf.find(node1) != uf.find(node2)){
                uf.union_(node1, node2);
            }
        }

        int res = INT_MAX;
        for(auto road : roads){
            int node1 = road[0], node2 = road[1], dist = road[2];
            if(uf.find(node1) == uf.find(1)){
                res = min(res, dist);
            }
        }

        return res;
    }
};

// BFS TC:O(V+E) SC:O(V+E)
class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        int res = INT_MAX;
        vector<vector<pair<int,int>>> graph(n+1);
        for(auto road : roads){
            graph[road[0]].push_back({road[1], road[2]});
            graph[road[1]].push_back({road[0], road[2]});
        } 

        vector<bool> visited(n+1);
        queue<int> q;
        q.push(1);
        
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto cur = q.front();
                q.pop();
                if(visited[cur]) continue;
                visited[cur] = 1;
                for(auto [neighbor, dist] : graph[cur]){
                    if(visited[neighbor]) continue;
                    res = min(res, dist);
                    q.push(neighbor);
                }
            }
        }

        return res;
    }
};

/*
求city 1 與 n 之間的 可能走過的路徑最小值為何
*/

