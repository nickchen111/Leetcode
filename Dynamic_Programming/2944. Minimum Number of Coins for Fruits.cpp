/*
2944. Minimum Number of Coins for Fruits
*/

// TC:O(n^2) SC:O(n)
class Solution {
    using LL = long long;
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        
        vector<LL> dp(n,INT_MAX/2);
        dp[0] = prices[0];
        
        for(int i = 1; i < n; i++){
            if(i == 1){
                dp[1] = dp[0];
                continue;
            }
            for(int j = i; 2*j + 1 >= i; j--){
                dp[i] = min(dp[i], prices[j] + dp[j-1]);
            }
        }

        return dp[n-1];
    }
};
/*
dp來考慮這題的話 
如果取了這個 後面 i個可以免費  但這項要花錢
不取的話 前面就是有cover到他的才行
dp[i] 目前看到 ith item 可能的最小值為多少 此題不能用取或者不取的思維建立兩個dp
雖然會認為不取的時候只要往前看到取的可以cover到他的程度即可 這段是沒問題的 但是很難界定說現在取那麼之前階段要拿哪一段的取or不取
拿可以cover到他的取是沒問題的 但是如果拿不取 那就意味著對方一定無法cover到他 那對方之所以可以不取是因為更前面有人取了 
更前面的人有沒有cover到我 無從界定
所以不分兩種狀態 端看現在這點能獲得最小值是多少就好

[1 2 3 4 5 ] -> [1 2] [2 3 4] [3 4 5 6] [4 5 6 7 8] [5 6 7 8 9 10] [6 7 8 9 10 11 12]

*/
