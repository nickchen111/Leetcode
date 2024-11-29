/*
1617. Count Subtrees With Max Distance Between Cities
*/

// TC:O(n*2^n) SC:O(n)
class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        vector<vector<int>> next(n);
        for(auto &e : edges) {
            next[e[0]-1].push_back(e[1]-1);
            next[e[1]-1].push_back(e[0]-1);
        }
        vector<int> res(n-1);
        int vis = 0;
        int state = 0;
        int d = 0;
        auto dfs = [&](auto &&dfs, int u) -> int {
            vis |= (1 << u);
            int maxLen = 0;
            for(auto &nxt : next[u]) {
                if(!((vis >> nxt) & 1) && ((state >> nxt) & 1)) {
                    int subLen = dfs(dfs, nxt) + 1;
                    d = max(d, maxLen + subLen);
                    maxLen = max(maxLen, subLen);
                }
            }
            
            return maxLen;
        };
        function<void(int i)> f = [&](int i) -> void {
            if(i == n) {
                if(state) {
                    vis = 0;
                    d = 0;
                    int cnt = 0;
                    while(((state >> cnt) & 1) == 0) {
                        cnt += 1;
                    }
                    dfs(dfs, cnt);
                }
                
                if(d && vis == state) {
                    res[d-1] += 1;
                }
                return;
            }
            f(i+1); // 不選
            state |= (1 << i);
            f(i+1);
            state ^= (1 << i);
        };
        f(0);

        return res;
        
    }
};

/*
要構造出 1-index 的res 來說 有多少個subtree 他的最長直徑 = index
*/
