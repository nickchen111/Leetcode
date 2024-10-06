/*
3310. Remove Methods From Project
*/

// TC:O(n+m) 點加邊 SC:O(n + m)
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<int> indegree(n);
        vector<vector<int>> next(n);
        for(auto inv : invocations){
            indegree[inv[1]] += 1;
            next[inv[0]].push_back(inv[1]);
        }
        vector<int> del(n);
        
        queue<int> q;
        q.push(k);
        int check = 0;
        int count = 0;
        if(indegree[k] == 0) {
            del[k] = 1;
            check += 1;
        }
        vector<bool> visited(n);
        
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int curNode = q.front();
                q.pop();
                if(visited[curNode]) continue;
                visited[curNode] = 1;
                count += 1;
                for(auto nxt : next[curNode]){
                    indegree[nxt] -= 1;
                    if(indegree[nxt] == 0) {
                        del[nxt] = 1;
                        check += 1;
                    }
                    q.push(nxt);
                }
            }
        }
      
        vector<int> res;
        if(check != count) {
            for(int i = 0; i < n; i++) {
                res.push_back(i);
            }
            
            return res;
        }
        else {
            for(int i = 0; i < n; i++){
                if(!del[i]) {
                    res.push_back(i);
                }
            }
            
            return res;
        }
        
    }
};
