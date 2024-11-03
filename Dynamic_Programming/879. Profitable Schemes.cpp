/*
879. Profitable Schemes
*/

// 遞推 + 遞歸
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {

        // 目前用的人數，賺取利潤，走到哪個group
        int m = group.size();
        // vector<vector<vector<int>>> memo(m, vector<vector<int>>(n+1, vector<int>(minProfit+1, -1)));
        /*
        遞推 未優化 TC:O(n*minProfit*m) SC:O(n*minProfit*m)
        vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(minProfit+1, 0)));
        for(int i = 0; i <= m; i++){
            for(int j = 0; j <= n; j++) {
                dp[i][j][0] = 1;
            }
        }
        for(int i = m-1; i >= 0; i--) {
            for(int j = n; j >= 0; j--) {
                for(int k = minProfit; k >= 0; k--) {
                    dp[i][j][k] = dp[i+1][j][k];
                    if(j - group[i] >= 0) dp[i][j][k] = (dp[i][j][k] + dp[i+1][j - group[i]][max(0,k - profit[i])]) % MOD;
                }
            }
        }

        return dp[0][n][minProfit];
        */
        // TC:O(n*minProfit*m) SC:O(n*minProfit)
        vector<vector<int>> dp(n+1, vector<int>(minProfit+1));
        
        for(int j = 0; j <= n; j++) {
            dp[j][0] = 1;
        }
        
        for(int i = m-1; i >= 0; i--) {
            for(int j = n; j >= 0; j--) {
                for(int k = minProfit; k >= 0; k--) {
                    dp[j][k] = dp[j][k];
                    if(j - group[i] >= 0) dp[j][k] = (dp[j][k] + dp[j - group[i]][max(0,k - profit[i])]) % MOD;
                }
            }
        }

        return dp[n][minProfit];
        /*
        遞歸 TC:O(n*minProfit*m) SC:O(n*minProfit*m)
        function<LL(int, int, int)> dfs = [&](int person, int leftProfit, int i) -> LL {
            if(person == 0) return leftProfit == 0 ? 1 : 0;
            if(i == m) return leftProfit == 0 ? 1 : 0;
            if(memo[i][person][leftProfit] != -1) return memo[i][person][leftProfit];

            int res = dfs(person, leftProfit, i+1) % MOD;
            if(group[i] <= person)
                res = (res + dfs(person - group[i], max(0, leftProfit - profit[i]), i+1)) % MOD;
            
            return memo[i][person][leftProfit] = res;
        };

        return dfs(n, minProfit, 0);
        */
    }
};
