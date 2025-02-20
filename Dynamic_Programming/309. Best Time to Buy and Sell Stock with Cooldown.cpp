/*
309. Best Time to Buy and Sell Stock with Cooldown
*/

// 2025. 02.20
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        
        vector dp(n+1, vector<int>(2, INT_MIN/2));
        dp[0][0] = 0;
        for(int i = 0; i < n; i++) {
            dp[i+1][0] = max(dp[i][0], dp[i][1] + prices[i]);
            dp[i+1][1] = max(dp[i][1], (i - 1 >= 0 ? dp[i-1][0] - prices[i] : 0 - prices[i]));
        }
        return dp[n][0];
        /*
        遞歸
        vector memo(n, vector<int>(2, INT_MIN/2));
        auto dfs = [&](auto &&dfs, int i, int j) -> int {
            if(i < 0) return j == 0 ? 0 : INT_MIN/2;
            int &ret = memo[i][j];
            if(ret != INT_MIN/2) return ret;
            if(j == 0) return ret = max(dfs(dfs, i-1, 0), dfs(dfs, i-1, 1) + prices[i]);
            return ret = max(dfs(dfs, i-1, 1), dfs(dfs, i-2, 0) - prices[i]);
        };
        return dfs(dfs,n-1,0);
        */
        
    }
};

//TC:O(n) SC:O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), 0);

        int sold = 0;
        int hold = INT_MIN/2;
        int cooled = 0;

        for(int i =1; i<=n; i++){
            int sold_tmp = sold, hold_tmp = hold, cooled_tmp = cooled;
            cooled = max(cooled_tmp, sold_tmp);
            hold = max(cooled_tmp-prices[i], hold_tmp);
            sold = hold_tmp+prices[i];
        }

        return max(sold, cooled);
    }
};

// sold = hold[i-1]+p;
// hold = max(cooled[i-1]-p, hold[i-1]);
// cooled = max(cooled[i-1],sold[i-1]);
