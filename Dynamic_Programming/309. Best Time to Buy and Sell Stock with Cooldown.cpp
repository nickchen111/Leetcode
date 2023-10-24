/*
309. Best Time to Buy and Sell Stock with Cooldown
*/

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
