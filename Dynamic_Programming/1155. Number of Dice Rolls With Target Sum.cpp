/*
1155. Number of Dice Rolls With Target Sum
*/

// 3/31
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numRollsToTarget(int n, int k, int target) {
        LL dp[n+1][target+1];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for(int j = 1; j <= min(target,k); j++){
            dp[1][j] = 1;
        }

        for(int i = 2; i <= n; i++){
            for(int j = target; j >= 0; j--){
                for(int t = 1; t <= k; t++){
                    if(j-t >= 0){
                        dp[i][j] = (dp[i][j] + dp[i-1][j-t]) %M;
                    }
                    else break;
                }
            }
        }

        return dp[n][target];
    }
};

// top down  TC:O(n*k*target) SC:O(k*target)
class Solution {
    long M = 1e9+7;
    int dp[31][1001];
public:
    int numRollsToTarget(int n, int k, int target) {
        for(int i = 0; i < 31; i++){
            for(int j = 0; j < 1000; j++){
                dp[i][j] = -1;
            }
        }
        long long res = solve(n,k,target)%M;

        return res;
        
    }
    long long solve(int n, int k, int target){
        if(n == 0 && target == 0) return 1;
        if(n < 0 || target < 0) return 0;
        if(dp[n][target] != -1) return dp[n][target];
        long long chance = 0;
        for(int i = 1; i <= k; i++){
            chance = (chance + solve(n-1, k, target - i)) % M;
        }

        dp[n][target] = chance;

        return chance;
    }
};

// bottom up TC:O(n*k*target) SC:O(k*target)
class Solution {
    long M = 1e9+7;
public:
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>> dp(n+1, vector<int>(target+1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= k; j++){
                for(int ta = j; ta <= target; ta++){
                    dp[i][ta] = (dp[i][ta] + dp[i-1][ta-j]) % M;
                }
            }
        }

        return dp[n][target];
    }
};


/*
投n個摋子with k 面 (1-k)種選擇 問有多少種組合可以累加出target
backtrack ? 30^30次方太大了
int dp[31][1001];
也就會是經過30輪時 可以達到1000的總數目為多少
DP -> 要達到target 1000 前面有可能的狀況是 target - k 要達到這個就是 target - 2*k可能
*/
