/*
2218. Maximum Value of K Coins From Piles
*/


// 遞推 + 遞歸
class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int n = piles.size();
        int m = piles[0].size();
        // TC:O(n*k*m) m為某物品的方案總數 SC:O(k)
        vector<int> dp(k+1, INT_MIN);
        dp[0] = 0;
        for(int i = 0; i < n; i++) {
            int p = piles[i].size();
            for(int j = k; j >= 0; j--) {
                int sum = 0;
                for(int t = 1; t <= min(p,j); t++) {
                    sum += piles[i][t-1];
                    dp[j] = max(dp[j], dp[j-t] + sum);
                }
            }
        }

        return dp[k];
        /*
        遞推 TC:O(n*k*m) m為某物品的方案總數 SC:O(n*k)
        vector<vector<int>> dp(n+1, vector<int>(k+1, INT_MIN));
        dp[0][0] = 0;
        for(int i = 0; i < n; i++) {
            for(int j = k; j >= 0; j--) {
                dp[i+1][j] = dp[i][j];
                int p = piles[i].size();
                int sum = 0;
                for(int t = 1; t <= min(p,j); t++) {
                    sum += piles[i][t-1];
                    dp[i+1][j] = max(dp[i+1][j], dp[i][j-t] + sum);
                }
            }
        }

        return dp[n][k];
        */
        // 狀態會是 某一堆中選了幾個?把它想成方案 加總到k就不能再選了
        /*
        遞歸 TC:O(n*k*m) m為某物品的方案總數 SC:O(n*k)
        vector<vector<int>> memo(n, vector<int>(k+1, -1));
        function<int(int i, int cnt)> dfs = [&](int i, int cnt) -> int {
            if(cnt < 0) return INT_MIN;
            if(i < 0) return 0;
            if(memo[i][cnt] != -1) return memo[i][cnt];
            int res = dfs(i-1, cnt);
            int sum = 0;
            int p = piles[i].size();
            for(int t = 1; t <= p; t++) {
                sum += piles[i][t-1];
                res = max(res, dfs(i-1, cnt-t) + sum);
            }

            return memo[i][cnt] = res;
        };

        return dfs(n-1, k);
        */
    }
};
