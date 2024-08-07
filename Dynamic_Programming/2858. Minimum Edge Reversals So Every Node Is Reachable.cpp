/*
2858. Minimum Edge Reversals So Every Node Is Reachable
*/

// TC:O(n) SC:O(n+m)
class Solution {
    using LL = long long;
    int count0 = 0;
    vector<int> res;
    unordered_set<LL> set;
    vector<vector<int>> next;
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        next.resize(n);
        for(auto edge : edges){
            set.insert(((LL)edge[0]<<32) | edge[1]);
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }
        res.resize(n);
        DFS(0,-1);
        
        reRoot(0,-1,count0);

        return res;
    }
    void DFS(int cur, int pa){
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            if(set.find(((LL)cur << 32) | nxt) == set.end()){
                count0 += 1;
            }
            DFS(nxt, cur);
        }
    }
    void reRoot(int cur, int pa, int count){
        res[cur] = count;
        for(auto nxt : next[cur]){
            int countNow = count;
            if(pa == nxt) continue;
            if(set.find(((LL)cur<<32) | nxt) == set.end()){
                countNow -= 1;                
            }
            if(set.find(((LL)nxt<<32) | cur) == set.end()){
                countNow += 1;
            }
            reRoot(nxt, cur, countNow);
        }
    }
};
