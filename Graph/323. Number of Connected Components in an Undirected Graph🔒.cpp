/*
323. Number of Connected Components in an Undirected Graph
在本题中，存在一个包含 n 个节点无向图。同时存在一个 edges 数组。其中 edges[i] = [a, b]，表示图中的节点 a 和节点 b 之间存在一条边。
你需要返回该图中连通分量的数量。

样例
样例 1
输入：
3
[[0,1], [0,2]]
输出：
1

样例 2
输入：
6
[[0,1], [1,2], [2, 3], [4, 5]]
输出：
2
*/

//DFS TC:O(n^2) SC:O(n)
class Solution {
    vector<bool> visited;
public:
    int countComponents(int n, vector<vector<int>> &edges) {
        //DFS
        vector<vector<int>> graph(n);
        visited = vector<bool>(n);

        for(auto edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int res = 0;
        for(int i =0; i<n; i++){
            if(!visited[i]){
                res+=1;
                DFS(graph,i);
            }
        }
    }
    void DFS(vector<vector<int>>& graph, int cur){
        if(visited[cur]) return;
        visited[cur] = true;
        for(int i = 0; i<graph[cur].size(); i++){
            DFS(graph,graph[cur][i]);
        }
    }
};

//BFS TC:O(n^2) SC:O(n)
class Solution {
public:
    int countComponents(int n, vector<vector<int>> &edges) {
        //BFS
        vector<vector<int>> graph(n);
        vector<bool> visited(n);
        for(auto edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int res = 0;
        queue<int> q;
        for(int i =0; i<n; i++){
            if(!visited[i]){
                q.push(i);
                res+=1;
                while(!q.empty()){
                    int cur = q.front();
                    q.pop();
                    visited[i] = true;
                    for(int j = 0; j<graph[cur].size(); j++){
                        if(!visited[graph[cur][j]])
                            q.push(graph[cur][j]);
                    }
                }
            }
        }

        return res;
    }
};

//Union_Find TC:O(N+Elg*E) SC:O(N) N為節點數 E為edge數量
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
    int countComponents(int n, vector<vector<int>> &edges) {
        //Union_Find
        UF uf(n);
        for(auto edge:edges){
            int  a = uf.find(edge[0]);
            int b = uf.find(edge[1]);
            if(a != b){
                n--;
                uf.union_(a,b);
            }
        }
        return n;
    }
};
