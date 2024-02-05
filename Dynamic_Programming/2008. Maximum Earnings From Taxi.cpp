/*
2008. Maximum Earnings From Taxi
*/

// TC:O(m+n+nlgn)
class Solution {
    using LL = long long;
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        vector<LL> dp(n+1);
        auto cmp = [](const vector<int>&a, const vector<int>& b){
            return a[1] < b[1];
        };
        sort(rides.begin(), rides.end(), cmp);
        int idx = 0;
        for(int i = 1; i <= n; i++){
            dp[i] = dp[i-1];
            while(idx < rides.size() && i == rides[idx][1]){
                LL start = rides[idx][0], end = rides[idx][1], tip = rides[idx][2];
                dp[i] = max(dp[i], dp[start] + end-start+tip); 
                idx++;
            }
        }

        return dp[n];
    }
};

/*
這題問說給你一堆客人上車與下車的點 還有會給小費
問你你一路開到底可以賺到的最多錢是多少 end-start + tip
可以放人下車與讓人上車在同一點
dp[i]定義成走到i點能獲取的最大收益
用二分去找出跟他起點一樣或者小於的點的最大收益
 x x x 
    x x x   
x x x x x x x 
              x x x  
                  x x x x
                x x x x x 
*/
