/*
2944. Minimum Number of Coins for Fruits
*/

// 4/6 
class Solution {
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(),0);
        vector<vector<int>> dp(n+1, vector<int>(2,INT_MAX));
        dp[0][0] = 0;
        dp[1][1] = prices[1];
        deque<int> dq; // 數值由小到大 裡面放index 並且是有取的狀態的
        dq.push_back(1);
        for(int i = 2; i <= n; i++){
            dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + prices[i];
            while(!dq.empty() && dp[dq.back()][1] >= dp[i][1]){
                dq.pop_back();
            }
            while(!dq.empty() && dq.front()*2 < i){
                dq.pop_front();
            }
            dq.push_back(i);
            dp[i][0] = dp[dq.front()][1];
        }

        return min(dp[n][1], dp[n][0]);
    }
};

// 雙狀態 + Deque  TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), -1);
        vector<LL> dp_take(n+1,INT_MAX/3);
        vector<LL> dp_notake(n+1,INT_MAX/3);
        dp_take[1] = prices[1];
        
        deque<int> dq;
        dq.push_back(1); // idx 遞增序列 頭為我們想要的最小值
        for(int i = 2; i <= n; i++){
            dp_take[i] = min(dp_take[i-1], dp_notake[i-1]) + prices[i];
            while(!dq.empty() && dp_take[dq.back()] > dp_take[i]){
                dq.pop_back();
            }
            while(!dq.empty() && dq.front()*2 < i){
                dq.pop_front();
            }
            dq.push_back(i);
            dp_notake[i] = dp_take[dq.front()];
            
        }

        int res = min(dp_take[n], dp_notake[n]);

        return res;
    }
};

// 雙狀態 取or不取 
class Solution {
    using LL = long long;
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), -1);
        vector<LL> dp_take(n+1,INT_MAX/3);
        vector<LL> dp_notake(n+1,INT_MAX/3);
        dp_take[1] = prices[1];
        
        for(int i = 2; i <= n; i++){
            for(int j = 1; j < i; j++){
                if(j + j >= i){
                    dp_notake[i] = min(dp_notake[i],dp_take[j]);
                }
            }
            dp_take[i] = min(dp_take[i-1], dp_notake[i-1]) + prices[i];
        }

        int res = min(dp_take[n], dp_notake[n]);

        return res;
    }
};

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
更新： 取or不取是可以做的 關鍵在於 dp 取的那段 每次都要從他前面一個挑 是要取 還是不取的比較小 而不能從 比他前面更久之前的挑 因為在那之前都還沒確定當下的前一個的合法性

*/
