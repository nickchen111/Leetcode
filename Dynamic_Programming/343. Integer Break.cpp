/*
343. Integer Break
*/

//iterative tc: 100% O(n^2) sc: O(n)
class Solution {
public:
    int integerBreak(int n) {
        
        vector<int> dp(n+1, INT_MIN);
        dp[2] = 1;

        for(int i = 3; i <= n; i++){
            for(int j = 1; j<i; j++){
                dp[i] = max(dp[i], j*max(i-j, dp[i-j]));
            }
        }
        return dp[n];

    }
};

//backtrack  tc: 100% O(n^2) sc: O(n)
class Solution {
    //recursion + memo
    vector<int> memo;
public:
    int integerBreak(int n) {
        memo = vector<int>(n+1, -1);
        vector<int> dp(n+1, INT_MIN);

        return backtrack(dp, n);
    }
    
    int backtrack(vector<int>& dp, int n){
        //base case
        if(n == 0) return 0;
        if(n == 1) return 1;
        if(n == 2) return 1;

        if(memo[n] != -1) return memo[n];

        for(int i = 1; i<=n/2; i++){
            dp[n] = max(dp[n], i*max(n-i, backtrack(dp, n-i)));
        }
        memo[n] = dp[n];

        return dp[n];
    }
};

/*
解題思路：
ex: 4 可以分解成 1 + 3 -> 1+ (2+1)-> 2+2
也就是說 1* (max(3, break(3))), 2* (max(2, break(2)))

*/
