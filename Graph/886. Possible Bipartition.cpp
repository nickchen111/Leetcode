/*
886. Possible Bipartition
*/

//DFS TC:O(V+E) SC:O(V)
class Solution {
    bool flag = true;
    vector<bool> visited;
    vector<bool> color;
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        //DFS
        //先建個鄰接表 某某不喜歡的人都加一加
        vector<vector<int>> graph(n+1);
        visited = vector<bool>(n+1,0);
        color = vector<bool>(n+1);
        
        for(int i = 0; i<dislikes.size(); i++){
            graph[dislikes[i][0]].push_back(dislikes[i][1]);
            graph[dislikes[i][1]].push_back(dislikes[i][0]);
        }

        for(int i = 1; i<=n; i++){
            if(visited[i]) continue;
            DFS(graph, i);
        }

        return flag;
    }
    void DFS(vector<vector<int>>& graph, int cur){
        if(flag == false) return;

        visited[cur] = true;
        for(auto neighbor:graph[cur]){
            if(!visited[neighbor]){
                color[neighbor] = !color[cur];
                visited[neighbor] = true;
                DFS(graph,neighbor);
            }
            else {
                if(color[cur] == color[neighbor]){
                    flag = false;
                    return;
                }
            }
        }
    }
};

// BFS:TC:O(V+E) SC:O(V)
class Solution {
    //bfs
public:
    vector<bool> color;
    vector<bool> visited;
    bool ok = true;
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        color.resize(n + 1);
        visited.resize(n + 1);
        vector<vector<int>> graph = vector<vector<int>>(n+1);
        graph = buildgraph(n, dislikes);

        for(int i = 1; i<=n; i++){
            if(!visited[i]){
                traverse(graph, i);
            }
        }

        return ok;
    }
    vector<vector<int>> buildgraph(int n, vector<vector<int>>& dislikes){
        vector<vector<int>> graph(n+1, vector<int>());

        for(auto edge:dislikes){
            int v = edge[1];
            int w = edge[0];
            //無向圖相當於雙向圖

            graph[v].push_back(w);
            graph[w].push_back(v);
        }

        return graph;
    }
    void traverse(vector<vector<int>>& graph, int start){

        visited[start] = true;
        queue<int> q;
        q.push(start);
        while(!q.empty() && ok){
            int v = q.front();
            q.pop();
        
            for(auto w:graph[v]){
                if(!visited[w]){
                    visited[w] = true;
                    color[w] = !color[v];
                    q.push(w);
                }
                else{
                    if(color[w] == color[v]){
                        ok = false;
                        return;
                    }
                }
            }
        }
    }
};
/*
解題思路：
此題即為互相討厭的人不能放在同一組 分兩組  互相討厭即為他們的edge-> 二分圖
與基礎題785不同的是 此次的關係圖不是直接給你 要自己build graph 剩下還是一樣的操作
dfs bfs
tc: o(V+E) sc: o(V+E)
*/
