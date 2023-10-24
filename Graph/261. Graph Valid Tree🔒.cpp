/*
261. Graph Valid Tree
*/


//DFS  TC:O(N+E) SC:O(N) N為節點數 E為edge數
class Solution {
    vector<bool> visited;
public:
    bool validTree(int n, vector<vector<int>> &edges) {
       vector<vector<int>> graph(n);
       visited = vector<bool>(n);

       for(auto edge:edges){
           graph[edge[0]].push_back(edge[1]);
           graph[edge[1]].push_back(edge[0]);
       }

       //相鄰的節點中是否有環
       if(!DFS(graph,0, -1)) return false;
       //是否有位連接任何點的點 或者自成一棵樹沒被遍歷到
       for(auto a:visited){
           if(!a) return false;
       }
       return true;
    }

    bool DFS(vector<vector<int>> graph, int cur, int pre){
        if(visited[cur]) return false;

        visited[cur] = true;
        for(auto neighbor:graph[cur]){
            if(neighbor != pre){
                if(!DFS(graph,neighbor,cur)) return false;
            }
        }
        return true;
    }
};

//Union_Find  TC:O(N+E) SC:O(N) 
class Solution {
    vector<int> parent;
    struct Uf{
        UF(int n){
            for(int i = 0; i<n; i++){
                parent.push_back(i);
            }
        }

        int find(int x){
            if(x != parent[x]){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        void Union_(int x, int y){
            x = find(x);
            y = find(y);
            if(x > y){
                parent[x] = y;
            }
            else parent[y] = x;
        }
    };
public:
    bool validTree(int n, vector<vector<int>> &edges) {
        UF uf(n);
        for(auto edge:edges){
            int a = uf.find(edge[0]);
            int b = uf.find(edge[1]);
            if(a != b){
                uf.union_(a,b);
            }
            else return false;
        }

        //看是否有其他棵樹
        for(int i = 1; i<n; i++){
            if(uf.find(i) != uf.find(i-1)) return false;
        }

        return true;
    }
};
