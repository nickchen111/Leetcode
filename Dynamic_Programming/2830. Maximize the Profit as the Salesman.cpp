/*
2830. Maximize the Profit as the Salesman
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[1] != b[1]) return a[1] < b[1];
            else return a[0] < b[0];
        };
        sort(offers.begin(), offers.end(), cmp);

        int res = 0;
        vector<int> dp(n,0);
        int idx = 0;
        for(int i = 0; i < n; i++){
            dp[i] = (i-1 < 0 ? 0 : dp[i-1]);
            while(idx < offers.size() && i == offers[idx][1]){
                int a = offers[idx][0], b = offers[idx][1], price = offers[idx][2];
                dp[i] = max(dp[b], (a-1 < 0 ? 0 : dp[a-1]) + price);
                idx++;
            }

            res = max(res, dp[i]);
        }

        return res;
    }
};

/*
有一整排房子 然後有一些買家出價購買某連續幾棟或者單獨一棟並且給定價格
問說你身為一個商人的最大利益可以是多少
等於是要想說很多個區間各自不重疊 能獲得的最大利益
dp[i] : 從0~i能獲得的最大利益 
先對offer做sort by ending point 每次找的時候要找當下點的start point之前最大的數值 
用sort by starting point 是錯的 例如以下情況
x x x x x x i
   x x x j
這樣子我先更新了到i的最大值可以是多少 才更新j 如此在i的時候答案就不對了 正確的寫法是sort by ending point 才能夠確立在當前end 每個點的數值
*/
