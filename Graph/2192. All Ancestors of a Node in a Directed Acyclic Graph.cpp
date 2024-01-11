/*
2192. All Ancestors of a Node in a Directed Acyclic Graph
*/

// DFS TC:O(n^2) SC:O(n^2)
class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for(auto edge : edges){
            graph[edge[0]].push_back(edge[1]);
        }
        res.resize(n);
        
        for(int i = 0; i < n; i++){
            vector<int> visited(n);
            DFS(i, i, graph, visited);
        }

        return res;
    }
    void DFS(int node, int cur, vector<vector<int>>& graph, vector<int>& visited){
        visited[cur] = 1;
        if(node != cur){
            res[cur].push_back(node);
        }

        for(auto neighbor : graph[cur]){
            if(visited[neighbor] == 0){
                DFS(node,neighbor, graph, visited);
            }
        }
    }
};

// Topological Sort + BFS TC:O(n^2*lgn) SC:O(n^2) 用了許多資料結構以及three pass所以跑比較慢
class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<int> visited(n);
        vector<vector<int>> graph(n);
        vector<set<int>> res(n);
        //先找出入度為0的點
        vector<int> indegree(n);
        for(auto edge : edges){
            graph[edge[1]].push_back(edge[0]);
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]] += 1;
        }

        queue<int> q;
        for(int i = 0; i < n; i++){
            if(indegree[i] == 0){
                q.push(i);
            }
        }

        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int node = q.front();
                q.pop();
                visited[node] = 1;
                for(auto neighbor : graph[node]){
                    if(visited[neighbor]){
                        //之前的
                        for(auto x : res[neighbor]){
                            res[node].insert(x);
                        }
                        //現在的
                        res[node].insert(neighbor);
                        
                    }
                    else {
                        indegree[neighbor] -= 1;
                        if(indegree[neighbor] == 0) {
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        vector<vector<int>> ans(n);
        for(int i = 0; i < n; i++){
            if(res[i].size() == 0) continue;
            for(auto x : res[i]){
                ans[i].push_back(x);
            }
        }

        return ans;
    }
};

/*
與1462有點類似 都是要找出前面有哪些點跟我是相關的
0~n-1
DAG
undirected edge a to b
去構造出每個點的祖先有哪些 按照升序排序
此題我第一個直接是topo來解 但是解的過程發現需要許多的資料結構配合 以及還要three pass材能構造出答案 整題時間複雜度是n*n*lgn 
但如果改成DFS思想 每一點都是去構築讓他下面的點能夠加入他 以這樣的方式可以將時間降到 n^2 並且因為是按照 0~n的順序去跑DFS所以按照升序排序的規則可以直接滿足
*/
