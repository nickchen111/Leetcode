/*
3243. Shortest Distance After Road Addition Queries I
*/

// TC:O(m*n) m 為query次數, n是節點數 SC:O(n)
class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> next(n);
        for(int i = 0; i < n-1; i++){
            next[i].push_back(i+1);
        }
        vector<int> res;
        
        for(int i = 0; i < queries.size(); i++){
            int a = min(queries[i][0], queries[i][1]);
            int b = max(queries[i][0], queries[i][1]);
            next[a].push_back(b);
            queue<int> q;
            q.push(0);
            int step = -1;
            vector<bool> visited(n);
            while(!q.empty()){
                bool flag = 0;
                int sz = q.size();
                step ++;
                while(sz--){
                    int cur = q.front();
                    q.pop();
                    if(cur == n-1) {
                        flag = 1;
                        res.push_back(step);
                        break;
                    }
                    visited[cur] = 1;
                    
                    for(auto nxt : next[cur]){
                        if(visited[nxt]) continue;
                        q.push(nxt);
                    }
                }
                
                if(flag) break;
            }
        }
        
        return res;
    }
};
