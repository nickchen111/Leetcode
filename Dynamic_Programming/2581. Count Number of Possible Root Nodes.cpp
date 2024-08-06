/*
2581. Count Number of Possible Root Nodes
*/

// TC:O(n) SC:O(n+m)
class Solution {
    using LL = long long;
    vector<vector<int>> next;
    unordered_set<LL> set;
    int res = 0;
    int count0 = 0;
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size();
        next.resize(n+1);
        for(auto edge : edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        for(auto g : guesses){
            set.insert(((LL)g[0]<<32) | g[1]);
        }
        DFS(0, -1);
        reRoot(0,-1, k, count0);
        
        return res;
    }
    void DFS(int cur, int pa){
        
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            if(set.find(((LL)cur<<32) | nxt) != set.end()) {
                count0 += 1;
            }
            DFS(nxt, cur);
        }

    }
    void reRoot(int cur, int pa, int k, int count){

        if(count >= k) res += 1;
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            int countNow = count;
            if(set.find(((LL)cur<<32) | nxt) != set.end()) {
                countNow -= 1;
            }
            if(set.find(((LL)nxt<<32) | cur) != set.end()) {
                countNow += 1;
            }
            reRoot(nxt, cur, k, countNow);
        }
    }
};
