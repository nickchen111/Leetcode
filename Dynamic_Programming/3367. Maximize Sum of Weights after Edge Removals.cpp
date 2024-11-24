/*
3367. Maximize Sum of Weights after Edge Removals
*/

// TC:O(nlgn + n) SC:O(n) 
class Solution {
    using LL = long long;
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        vector<vector<pair<int,int>>> next(n);
        for(auto &edge : edges) {
            next[edge[0]].push_back({edge[1], edge[2]});
            next[edge[1]].push_back({edge[0], edge[2]});
        }
        
        auto dfs = [&](auto& dfs, int x, int prev) -> pair<LL, LL>{
            LL not_choose = 0;
            vector<LL> incr;
            for(auto &[nxt, wt] : next[x]) {
                if(nxt == prev) continue;
                auto [nc,c] = dfs(dfs, nxt, x);
                not_choose += nc; // 先都不選
                if(c + wt - nc > 0) {
                    incr.push_back(c + wt - nc); // 之前的讓你這次可以選並且選了有好處的
                }
            }
           
            sort(incr.rbegin(), incr.rend());
            for(int i = 0; i < min(k-1, (int)incr.size()); i++) {
                not_choose += incr[i];
            }
            LL choose = not_choose;
            if(incr.size() >= k) {
                not_choose += incr[k-1];
            }
            
            return {not_choose, choose};  
        };
        
        auto [nc,c] = dfs(dfs, 0, -1);
        return max(nc, c);
    }
};
