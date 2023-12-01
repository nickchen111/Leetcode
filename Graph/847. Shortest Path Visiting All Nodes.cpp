/*
847. Shortest Path Visiting All Nodes
*/


// 最佳解 from好的資料結構 TC:O(n*2^n) SC:O(n*2^n)
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int finalState = 0;
        
        for(int i = 0; i<n; i++){
            finalState |= (1<<i);
        }
        
        queue<pair<int,int>> q; // node state
        auto visited = vector<vector<bool>>(n, vector<bool>(1<<n));//紀錄每個走到每個點時曾經有過的狀態
        //多源BFS
        
        for(int i = 0; i<n; i++){
            q.push({i,1<<i});
        }

        int step = -1;
        while(!q.empty()){
            int len = q.size();
            step++;
            while(len--){
                int node = q.front().first;
                int state = q.front().second;
                q.pop();
                for(const auto &neighbor:graph[node]){
                    int nextState = state | (1<<neighbor);
                    if(nextState == finalState) return step+1;
                    if(visited[neighbor][nextState] == 0){
                        q.push({neighbor,nextState});
                        visited[neighbor][nextState] = 1;
                    }
                }
            }
        }

        return 0;
    }
};

//次佳解 vector<unordered_set<int>>(n);
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int finalState = 0;
        
        for(int i = 0; i<n; i++){
            finalState |= (1<<i);
        }
        
        queue<pair<int,int>> q; // node state
        auto visited = vector<unordered_set<int>>(n); //紀錄每個走到每個點時曾經有過的狀態
        //多源BFS
        
        for(int i = 0; i<n; i++){
            q.push({i,1<<i});
        }

        int step = -1;
        while(!q.empty()){
            int len = q.size();
            step++;
            while(len--){
                int node = q.front().first;
                int state = q.front().second;
                q.pop();
                for(const auto &neighbor:graph[node]){
                    int nextState = state | (1<<neighbor);
                    if(nextState == finalState) return step+1;
                    if(visited[neighbor].find(nextState) == visited[neighbor].end()){
                        q.push({neighbor,nextState});
                        visited[neighbor].insert(nextState);
                    }
                }
            }
        }

        return 0;
    }
};
