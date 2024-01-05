/*
1129. Shortest Path with Alternating Colors
*/

// TC:O(V+E) SC:O(V+E)
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<pair<int,int>>> graph(n);
        // red : 0
        for(auto edge : redEdges){
            graph[edge[0]].push_back({edge[1],0});
        }
        // blue : 1
        for(auto edge : blueEdges){
            graph[edge[0]].push_back({edge[1],1});
        }

        vector<int> res(n,-1);
        res[0] = 0;
        queue<vector<int>> q;
        q.push({0,-1,0});
       
        while(!q.empty()){
            int node = q.front()[0];
            int color = q.front()[1];
            int step = q.front()[2];
            q.pop();
           

            for(auto &adj : graph[node]){
                if(color != adj.second && adj.first != -1){
                    q.push({adj.first, adj.second, step+1});
                    res[adj.first] = res[adj.first] != -1 ? res[adj.first] : step+1;
                    adj.first = -1;// 代表走過了 好處是可以標記成是從紅線還是藍線的走過了    
                } 
            }
        
        }

        
        return res;
    }
};

/*
有一堆node 每條node可以是單向或者雙向 並且會用藍紅顏色標記
return 從0到任意點有沒有辦法不連續走相同顏色抵達 並且求出他的最短路徑
my thought :
graph node1 ->node2 with what color by BFS

*/
