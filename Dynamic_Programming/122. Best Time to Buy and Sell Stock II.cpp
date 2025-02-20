/*
122. Best Time to Buy and Sell Stock II
*/

// 2025.02.20
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // 空間壓縮
        int hold = INT_MIN/2, unhold = 0;
        for(int i = 0; i < n; i++) {
            int prev_hold = hold;
            hold = max(hold, unhold - prices[i]);
            unhold = max(unhold, prev_hold + prices[i]);
        }
        return unhold;
        /*
        遞推
        vector dp(n+1, vector<int>(2, INT_MIN));
        dp[0][0] = 0;
        for(int i = 0; i < n; i++) {
            dp[i+1][1] = max(dp[i][1], dp[i][0] - prices[i]);
            dp[i+1][0] = max(dp[i][0], dp[i][1] + prices[i]);
        }
        return dp[n][0];
        */
        /*
        遞推
        vector memo(n, vector<int>(2, INT_MIN/2));
        auto dfs = [&](auto &&dfs, int i, int j) -> int {
            if(i < 0) {
                return j == 0 ? 0 : INT_MIN/2;
            }
            int &ret = memo[i][j];
            if(ret != INT_MIN/2) return memo[i][j];
            if(j == 1) return ret = max(dfs(dfs, i-1, 1), dfs(dfs, i-1, 0) - prices[i]);
            return ret = max(dfs(dfs, i-1, 0), dfs(dfs, i-1, 1) + prices[i]);
        };
        return dfs(dfs, n-1, 0);
        */
    }
};

//雙狀態的dp類型 直接定義 當前天數的最大收益 然後可能的雙狀態   TC:O(n) SC:O(2*n)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), 0);

        vector<vector<int>> dp(n+1, vector<int>(2));
        dp[1][0] = 0;
        dp[1][1] = -prices[1];

        for(int i = 2; i<=n; i++){
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);
            dp[i][1] = max(dp[i-1][0]-prices[i], dp[i-1][1]);
        }

        return dp[n][0];
    }
};

//空間優化：TC:O(n) SC:O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), 0);

        int sold = 0;
        int hold = -prices[1];

        //老套路了 開個空間紀錄前一次的結果 現在的結果會跟之前有關
        for(int i = 2; i<=n; i++){
            int sold_old = sold; int hold_old = hold;
            sold = max(sold_old, hold_old+prices[i]);
            hold = max(hold_old, sold_old-prices[i]);
        }

        return sold;
    }
};

/*
121基本題型的follow up
可以買進賣出不限次數 也可以當天買賣 求最大收益
dp[i][狀態]：定義在當前天數之前能夠買賣的最大收益
 i為當前天數 狀態可為持有股票or未持有股票
*/
