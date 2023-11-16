/*
1971. Find if Path Exists in Graph
*/


// DFS TC:O(n+E) SC:O(n+E)
class Solution {
    vector<bool> visited;
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        //DFS

        vector<vector<int>> graph(n);
        visited.resize(n);
        for(auto edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        return DFS(graph,source,destination);
    }
    bool DFS(vector<vector<int>>& graph, int source, int destination){
        if(source == destination) return true;
        visited[source] = true;
        for(auto neighbor:graph[source]){
            if(visited[neighbor]) continue;
            if(DFS(graph,neighbor,destination) == true) return true;
        }
        
        return false;

    }
};

// Union_Find TC:O(n) SC:O(n)
class Solution {
    struct UF{
        vector<int> parent;
        UF(int n){
            for(int i=0; i<n; i++){
                parent.push_back(i);
            }
        }
        int find(int x){
            if(x != parent[x]){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        void union_(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            if(rootx != rooty) parent[rootx] = rooty;
        }
        bool isConnected(int x,int y){
            int rootx = find(x);
            int rooty = find(y);
            if(rootx == rooty) return true;
            else return false;
        }
    };
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        UF uf(n);
        for(auto edge:edges){
            uf.union_(edge[0],edge[1]);
        }
        if(uf.find(source) != uf.find(destination)) return false;
        else return true;
    }
};
