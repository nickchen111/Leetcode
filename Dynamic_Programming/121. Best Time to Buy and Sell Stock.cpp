/*
121. Best Time to Buy and Sell Stock
*/

//股票買賣問題限制只能買賣一次  用dp[i][買的狀態 or賣] 根據題目意思去設計當前最大收益狀態
//TC:O(n) SC:(2*n)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), 0);//未開市日

        vector<vector<int>> dp(n+1, vector<int>(2));//狀態只會有買or賣

        dp[0][0] = 0;//第一天也沒辦法買
        dp[0][1] = INT_MIN/2;

        for(int i = 1; i<=n; i++){
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);
            dp[i][1] = max(dp[i-1][1], -prices[i]);
        }


        return dp[n][0];
    }
};

//此為下一個寫法的空間為優化方式
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> min_prices(n);
        vector<int> max_profit(n);
        min_prices[0] = prices[0];
        max_profit[0] = 0;
        for(int i = 1; i < n; i++ ){
            min_prices[i] = min(min_prices[i-1], prices[i]);
            max_profit[i] = max(max_profit[i-1], prices[i]- min_prices[i-1]);
        }
        return max_profit[n-1];
        }
};

//空間優化 且只去記錄當前最小值 跟目前可能的最大值 去動態取得當前天數之前的最大收益time:O(n) space:O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int minVal = prices[0];
        int maxVal = 0;//第一天不能賣

        for(int i = 1; i <n; i++){
            minVal = min(minVal, prices[i]);
            maxVal = max(maxVal, prices[i] - minVal);
        }

        return maxVal;
    }
};


/*
建立一個dp數組 去紀錄到第i天可以買or賣的僅僅一次的最大收益狀況 之後取所有天數皆可選擇的狀況且已賣出即可
*/
