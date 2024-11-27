/*
2246. Longest Path With Different Adjacent Characters
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
        int n = s.size();
        vector<vector<int>> next(n);
        for(int i = 1; i < n; i++) {
            next[parent[i]].push_back(i);
        }
       
        int res = 0;
        auto dfs = [&](auto &&dfs, int i) -> int {
            int maxVal = 0;
            int secondMaxVal = 0;
            for(auto &nxt : next[i]) {
                if(s[nxt] != s[i]) {
                    int cur = dfs(dfs, nxt);
                    if(cur > maxVal) {
                        secondMaxVal = maxVal;
                        maxVal = cur;
                    }
                    else if(cur > secondMaxVal) {
                        secondMaxVal = cur;
                    }
                }
                else {
                    dfs(dfs, nxt);
                }
            }

            res = max(res, 1 + maxVal + secondMaxVal);
            return 1 + maxVal;
        };
        dfs(dfs, 0);
        return res;
    }
};
