// TC:O(n + m) m為最後會走到的節點數 SC:O(n)
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> next(n);
        vector<int> outdegree(n);
        for(int i = 0; i < n; i++) {
            for(auto &j : graph[i]) {
                next[j].push_back(i);
                outdegree[i] += 1;
            }
        }
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(outdegree[i] == 0) q.push(i);
        }
        vector<int> ans;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(int nxt : next[node]) {
                outdegree[nxt] -= 1;
                if(outdegree[nxt] == 0) q.push(nxt);
            }
        }
        for(int i = 0; i < n; i++) {
            if(outdegree[i] == 0) ans.push_back(i);
        }
        return ans;
    }
};
