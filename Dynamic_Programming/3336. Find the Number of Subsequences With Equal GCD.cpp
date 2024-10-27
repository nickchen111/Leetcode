/*
3336. Find the Number of Subsequences With Equal GCD
*/

// 遞歸 & 遞推: TC:O(n*k^2) SC:O(n*k^2)
class Solution {
    using LL = long long;
public:
    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        LL MOD = 1e9 + 7;
        vector<vector<vector<LL>>> memo(n, vector<vector<LL>>(201, vector<LL>(201, -1)));
        function<LL(int i, int j, int k)> dfs = [&] (int i, int j, int k) -> LL {
            if(i < 0) return (j == k);
            if(memo[i][j][k] != -1) return memo[i][j][k];
            
            return memo[i][j][k] = (dfs(i-1, j, k) + dfs(i-1, gcd(j, nums[i]), k) + dfs(i-1, j, gcd(k,nums[i]))) % MOD;
        };
        
        return (dfs(n-1, 0, 0) - 1 + MOD) % MOD;
    }
};


class Solution {
    using LL = long long;
public:
    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        LL MOD = 1e9 + 7;
        LL maxVal = *max_element(nums.begin(), nums.end());
        vector<vector<vector<LL>>> dp(n+1, vector<vector<LL>>(maxVal + 1, vector<LL>(maxVal + 1, 0)));
//         function<LL(int i, int j, int k)> dfs = [&] (int i, int j, int k) -> LL {
//             if(i < 0) return (j == k);
//             if(memo[i][j][k] != -1) return memo[i][j][k];
            
//             return memo[i][j][k] = (dfs(i-1, j, k) + dfs(i-1, gcd(j, nums[i]), k) + dfs(i-1, j, gcd(k,nums[i]))) % MOD;
//         };
        
        dp[0][0][0] = 1;
        LL res = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= maxVal; j++) {
                for(int k = 0; k <= maxVal; k++) {
                    dp[i+1][j][k] = (dp[i+1][j][k] + dp[i][j][k]) % MOD;
                    dp[i+1][gcd(j, nums[i])][k] = (dp[i+1][gcd(j, nums[i])][k] + dp[i][j][k]) % MOD;
                    dp[i+1][j][gcd(k, nums[i])] = (dp[i+1][j][gcd(k, nums[i])] + dp[i][j][k]) % MOD;
                }
            }
        }
        
        
        for(int j = 1; j <= maxVal; j++) {
            res = (res + dp[n][j][j]) % MOD;
        }
        
        return res;
    }

    int gcd(int a, int b) {
        while(b) {
            int t = a % b;
            a = b;
            b = t;
        }

        return a;
    }
};
