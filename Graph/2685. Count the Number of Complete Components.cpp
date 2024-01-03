/*
2685. Count the Number of Complete Components
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<bool> visited;
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> indegree(n);
        vector<vector<int>> graph(n);
        for(auto &edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
            indegree[edge[1]] += 1;
            indegree[edge[0]] += 1;
        }
        
        visited.resize(n);
        int res = 0;
        // find every groupsize
        for(int i = 0; i < n; i++){
            if(visited[i]) continue;
            vector<int> temp;
            DFS(graph,i, temp);
            bool flag = 0;
            for(auto x : temp){
                if(indegree[x] != temp.size()-1){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0) res += 1;
        }

        return res;
    }

    void DFS(vector<vector<int>>& graph, int cur, vector<int>& temp){

        visited[cur] = 1;
        temp.push_back(cur);
        for(auto neighbor : graph[cur]){
            if(visited[neighbor]) continue;
            DFS(graph,neighbor,temp);
        }
    }
};

/*
按照題目說明 某一團中如果大家的入度或者出度都等於這團數量-1那就是合法的graph
*/
