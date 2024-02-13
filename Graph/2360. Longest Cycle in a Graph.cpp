/*
2360. Longest Cycle in a Graph
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<int> indegree(n,0);
        vector<vector<int>> graph(n);
        for(int i = 0; i < n; i++){
            if(edges[i] == -1) continue;
            indegree[edges[i]] += 1;
            graph[i].push_back(edges[i]);
            graph[edges[i]].push_back(i);
        }
        vector<bool> visited(n,0);
        queue<int> q;
        for(int i = 0; i < n; i++){
            if(indegree[i] == 0) q.push(i);
        }

        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int curNode = q.front();
                q.pop();
                if(visited[curNode]) continue;
                visited[curNode] = 1;
                for(auto x : graph[curNode]){
                    if(visited[x]) continue;
                    indegree[x] -= 1;
                    if(indegree[x] == 0) q.push(x);
                }
            }
        }

        int res = -1;
        for(int i = 0; i < n; i++){
            if(visited[i]) continue;
            q.push(i);
            int count = 0;
            while(!q.empty()){
                int sz = q.size();
                while(sz--){
                    int curNode = q.front();
                    q.pop();
                    if(visited[curNode]) continue;
                    visited[curNode] = 1;
                    count += 1;
                    for(auto x : graph[curNode]){
                        if(visited[x]) continue;
                        q.push(x);
                    }
                }
            }
            res = max(res, count);
        }

        return res;
    }
};

/*
graph 0~n-1 每個點最多有一條outdegree edge 找出這個圖中最長的cycle
如果沒有return -1
1. how to detect cycle -> 透過visited數組
another way topological sort  將入度為0的刪掉 剩下的就會是圓
2. how to find out the logest length of cycle
*/
