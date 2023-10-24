/*
714. Best Time to Buy and Sell Stock with Transaction Fee
*/


//TC:O(n SC:O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        prices.insert(prices.begin(), 0);
        int sold = 0; 
        int hold = INT_MIN/2;

        for(int i = 1; i<=n; i++){
            int sold_tmp = sold, hold_tmp = hold;
            sold = max(sold_tmp, hold_tmp+prices[i]-fee);//手續費定在賣出的時候扣
            hold = max(hold_tmp, sold_tmp-prices[i]);
        }

        return sold; 
    }
};

/*
這題是stock II 的follow up 多了個買賣的手續費
*/
