/*
2392. Build a Matrix With Conditions
*/

// TC:O(k) SC:O(k)
class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> res(k, vector<int>(k));
        vector<int> row = topo(k, rowConditions);// 1-k 從上到下順序
        vector<int> col = topo(k, colConditions);// 1-k 從左到右順序

        if(row.empty() || col.empty()) return {};
        vector<pair<int,int>> pos(k+1);
        for(int i = 0; i < k; i++){
            pos[row[i]].first = i; // 某個數字的row在哪行
        }
        for(int i = 0; i < k; i++){
            pos[col[i]].second = i;// 某個數字的col在哪列
        }

        for(int i = 1; i <= k; i++){
            res[pos[i].first][pos[i].second] = i;
        }

        return res;
    }
    vector<int> topo(int k, vector<vector<int>>& conditions){
        vector<vector<int>> next(k+1);
        vector<int> indegree(k+1);
        for(auto c : conditions){
            next[c[0]].push_back(c[1]);
            indegree[c[1]] += 1;
        }

        queue<int> q;
        for(int i = 1; i <= k; i++){
            if(indegree[i] == 0) q.push(i);
        }
        vector<int> res;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int cur = q.front();
                res.push_back(cur);
                q.pop();
                for(auto nxt : next[cur]){
                    indegree[nxt] -= 1;
                    if(indegree[nxt] == 0) q.push(nxt);
                }
            }
        }

        if(res.size() != k) return {};

        return res;
    }
};
