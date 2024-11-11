/*
1155. Number of Dice Rolls With Target Sum
*/

// 遞推 + 遞歸 
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numRollsToTarget(int n, int k, int target) {
        
        // 遞推 TC:O(n*target*k) SC:O(target)
        vector<LL> dp(target+1);
        dp[0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = target; j >= 0; j--) {
                dp[j] = 0;
                for(int t = 1; t <= k; t++) {
                    if(j - t >= 0) {
                        dp[j] = (dp[j] + dp[j-t]) % MOD;
                    }
                    else break;
                }
            }
        }
        return dp[target];
        
        /*
        遞歸 TC:O(n*target*k) SC:O(n*target)
        vector<vector<LL>> memo(n, vector<LL>(target+1, -1));
        function<LL(int i, int sum)> dfs = [&](int i, int sum) -> LL {
            if(i < 0 && sum == 0) return 1;
            if(sum < 0) return 0;
            if(i < 0) return 0;
            if(memo[i][sum] != -1) return memo[i][sum];
            LL res = 0;
            for(int j = 1; j <= k; j++) {
                res = (res + dfs(i-1, sum - j)) % MOD;
            }

            return memo[i][sum] = res;
        };

        return dfs(n-1, target);
        */
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
