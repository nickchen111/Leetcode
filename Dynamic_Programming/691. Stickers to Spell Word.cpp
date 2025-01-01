/*
691. Stickers to Spell Word
*/

// TC:O(n*m*2^n) SC:O(2^n)
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int m = stickers.size();
        vector<vector<int>> arr(m, vector<int>(26)); 
        for(int i = 0; i < m; i++) {
            for(auto &ch : stickers[i]) {
                arr[i][ch-'a'] += 1;
            }
        } 

        int n = target.size();
        vector<int> dp(1 << n, INT_MAX/2);
        dp[(1 << n) - 1] = 0;
        for(int state = (1 << n) - 2; state >= 0; state --) {
            for(int i = 0; i < m; i++) {
                vector<int> tmp = arr[i];
                int new_state = state;
                for(int j = 0; j < n; j++) {
                    if(((state >> j) & 1) == 0 && tmp[target[j]-'a'] > 0) {
                        tmp[target[j]-'a'] -= 1;
                        new_state |= (1 << j);
                    }
                }
                dp[state] = min(dp[state], dp[new_state] + 1);
            }
        }

        return dp[0] == INT_MAX/2 ? -1 : dp[0];
        /*
        遞歸 TC:O(n*m*2^n) SC:O(2^n)
        vector<int> memo(1 << n, -1);
        auto dfs = [&](auto &&dfs, int mask) -> int {
            if(mask == (1 << n) - 1) return 0;
            if(memo[mask] != -1) return memo[mask];
            int ret = INT_MAX/2;
            for(int i = 0; i < m; i++) {
                int new_mask = mask;
                bool flag = 0;
                vector<int> tmp(arr[i]);
                for(int j = 0; j < n; j++) {
                    if(((mask >> j) & 1) == 0 && tmp[target[j]- 'a'] > 0) {
                        tmp[target[j]-'a'] -= 1;
                        new_mask |= (1 << j);
                        flag = 1;
                    }
                }

                if(flag) {
                    ret = min(ret, 1 + dfs(dfs, new_mask));
                }
            }
            return memo[mask] = ret;
        };


        int res = dfs(dfs, 0);
        return res == INT_MAX/2 ? -1 : res;
        */

    }
};
