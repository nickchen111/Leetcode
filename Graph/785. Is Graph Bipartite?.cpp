/*
785. Is Graph Bipartite?
*/

// 2025.01.30 
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> next(n);
        for(int i = 0; i < n; i++) {
            for(auto &e : graph[i]) {
                next[i].push_back(e);
                next[e].push_back(i);
            }
        }
        vector<int> color(n);
        auto dfs = [&](auto &&dfs, int i, int c) -> bool {
            color[i] = c;
            for(auto &nxt : next[i]) {
                if(color[nxt] == c || (color[nxt] == 0 && !dfs(dfs, nxt, 3 - c))) return false;
            }
            return true;
        };
        for(int i = 0; i < n; i++) {
            if(color[i]) continue;
            if(!dfs(dfs, i, 1)) return false;
        }
        return true;
    }
};

// 12/14 DFS
class Solution {
    vector<int> color;
    vector<bool> visited;
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        color.resize(n);
        visited.resize(n);

        for(int i = 0; i < n; i++){
            if(DFS(graph,i) == false) return false;
        }

        return true;
    }

    bool DFS(vector<vector<int>>& graph, int cur){
        
        visited[cur] = 1;
        for(auto neighbor : graph[cur]){
            if(visited[neighbor] == 1){
                if(color[neighbor] == color[cur]) return false;
            }
            else {
                color[neighbor] = !color[cur];
                visited[neighbor] = 1;
                if(!DFS(graph,neighbor)) return false;
            }
        }

        return true;
    }
};


class Solution {
    //dfs
public:
    vector<bool> visited;
    vector<bool> color;
    bool ok = true;
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        color.resize(n);
        visited.resize(n);
        // 因为图不一定是联通的，可能存在多个子图
        // 所以要把每个节点都作为起点进行一次遍历
        // 如果发现任何一个子图不是二分图，整幅图都不算二分图
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                traverse(graph, v);
            }
        }
        return ok;
    }

    // DFS 遍历框架
    void traverse(vector<vector<int>>& graph, int v) {
        // 如果已经确定不是二分图了，就不用浪费时间再递归遍历了
        if (!ok) return;

        visited[v] = true;
        for (int w : graph[v]) {
            if (!visited[w]) { //原本是寫在上面當base case但果是二分圖要改成寫在這裡來判斷 因為多了些條件else
                // 相邻节点 w 没有被访问过
                // 那么应该给节点 w 涂上和节点 v 不同的颜色
                color[w] = !color[v];
                // 继续遍历 w
                traverse(graph, w);
            } else {
                // 相邻节点 w 已经被访问过
                // 根据 v 和 w 的颜色判断是否是二分图
                if (color[w] == color[v]) {
                    // 若相同，则此图不是二分图
                    ok = false;
                    return;
                }
            }
        }
    }
};


class Solution {
    //bfs
public:
    vector<bool> visited;
    vector<bool> color;
    bool ok = true;
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        color.resize(n);
        visited.resize(n);
        // 因为图不一定是联通的，可能存在多个子图
        // 所以要把每个节点都作为起点进行一次遍历
        // 如果发现任何一个子图不是二分图，整幅图都不算二分图
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                traverse(graph, v);
            }
        }
        return ok;
    }

    // BFS 遍历框架
    void traverse(vector<vector<int>>& graph, int start) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while(!q.empty() && ok){
            int v = q.front(); q.pop();
            for(auto w:graph[v]){
                if(!visited[w]){
                    color[w] = !color[v];
                    visited[w] = true;
                    q.push(w);
                }
                else {
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
二分圖Bipartite 基礎題
二分圖 需要用到visited數組 color ok三個數組
dfs: 
tc: o(V+E) sc: o(V)
bfs:
tc: o(V+E) sc: o(V)
*/
