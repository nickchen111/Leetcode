/*
2787. Ways to Express an Integer as Sum of Powers
*/


//  TC:O(target*n) SC:O(target)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numberOfWays(int n, int x) {
        vector<LL> dp(n+1);
        dp[0] = 1;
        // x次方 
        for(int i = 1; pow(i,x) <= n; i++){
            for(int sum = n; sum >= pow(i,x); sum--){
                dp[sum] += dp[sum-pow(i,x)];
            }
        }

        return dp[n]%M;

    }
};

// 第二種多開數組寫法 TC:O(target*n) SC:O(target)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numberOfWays(int n, int x) {
        vector<LL> dp(n+1);
        dp[0] = 1;
        // x次方 
        for(int i = 1; pow(i,x) <= n; i++){
            auto dp_tmp = dp;
            for(int sum = 0; sum <= n ; sum++){
                if(pow(i,x) > sum) continue;
                dp[sum] += dp_tmp[sum-pow(i,x)];
            }
        }

        return dp[n]%M;

    }
};


/*
很像之前的279 DP題 某個數字拆解後的平方最大值
但這題其實不太一樣 這題要問說 某個數 能否用某些數的x次方拼湊出的可能性有多少
所以 3^2+1^2 跟 1^2+3^2這種的要算是同一種不能重複計算 並且每個數字只能用一次 明顯的01背包問題
*/
