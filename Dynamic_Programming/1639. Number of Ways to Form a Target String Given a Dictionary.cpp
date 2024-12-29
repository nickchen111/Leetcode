/*
1639. Number of Ways to Form a Target String Given a Dictionary
*/

// TC:O(n*m) SC:O(n*m)
class Solution {
    using LL = long long;
    const LL MOD = 1e9 + 7;
public:
    int numWays(vector<string>& words, string target) {
        int n = words[0].size();
        int m = target.size();
        if(n < m) return 0;
        vector<vector<LL>> arr(n, vector<LL>(26,0));
        for(auto &word : words){
            for(int i = 0; i < word.size(); i++) {
                // cout << word[i] << ' ' << i << endl;
                arr[i][word[i]-'a'] += 1;
            }
        }
        vector<vector<LL>> dp(n+1, vector<LL>(m+1, 0));
        for(int j = 0; j <= n; j++) dp[j][0] = 1;
        for(int i = 0;i < n; i++){
            for(int j = 0;j < m ;j++){
                dp[i + 1][j + 1] = (int)(((long)arr[i][target[j] - 'a'] * dp[i][j] + dp[i][j + 1]) % MOD);
            }
        }

        return dp[n][m];
        /*
        遞歸 TC:O(m*n) SC:O(m*n)
        vector<vector<LL>> memo(n, vector<LL>(m, -1));
        auto dfs = [&](auto &&dfs, int i, int j) -> LL {
            if(j == m) return 1;
            if(i == n) return 0;
            if(memo[i][j] != -1) return memo[i][j];
            LL ret = dfs(dfs, i+1, j) % MOD;
            if(arr[i][target[j]-'a'] != 0) ret = (ret + arr[i][target[j]-'a'] * dfs(dfs, i+1, j+1)) % MOD;

            return memo[i][j] = ret;
        };

        return dfs(dfs, 0, 0);
        */
    }
};

/*
可以先預處理 每個index之前能有哪些字母可以選
dp[i][j] 處理到第i個target的字，用到第j個index 會有多少種方法組成
*/
