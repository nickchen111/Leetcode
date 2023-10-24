/*
70. Climbing Stairs
*/

//iterative tc: O(n) sc: O(n) 可在優化
class Solution {
    //iterative 
public:
    int climbStairs(int n) {
        if(n == 1 || n == 2) return n;
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        dp[2] = 2;

        for(int i = 3; i<=n; i++){
            dp[i] = dp[i-1]+dp[i-2];
        }

        return dp[n];
    }
};


//優化 tc:O(n) sc: O(1)
class Solution {
    //iterative 
public:
    int climbStairs(int n) {
        if(n == 1 || n == 2) return n;

        int prev = 1;
        int cur = 2;

        for(int i = 3; i<=n; i++){
            int sum = prev+cur;
            prev = cur;
            cur = sum;
        }

        return cur;
    }
};

//recursion+memo 
class Solution {
    //recursion+memo
    vector<int> memo;
public:
    int climbStairs(int n) {
        memo = vector<int>(n+1, -1);

        return backtrack(n);
    }
    int backtrack(int n){
        if(n == 1 || n == 2) return n;
        if(memo[n] != -1) return memo[n];

        int res = backtrack(n-1) + backtrack(n-2); 
        memo[n] = res;

        return res;
    }
};
