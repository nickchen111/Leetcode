/*
2518. Number of Great Partitions
*/

// 遞推 + 遞歸
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        if(reduce(nums.begin(), nums.end(), 0LL) < 2*k) return 0;
        function<LL(LL,LL)> quickMul = [&](LL a, LL b) -> LL {
            LL ans = 1;
            while(b) {
                if(b&1) ans = (ans*a) % MOD;
                a = (a*a) % MOD;
                b >>= 1;
            }

            return ans;
        };
        // TC:O(n*k) SC:O(k)
        
        vector<LL> dp(k);
        dp[0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = k-1; j >= nums[i]; j--) {
                dp[j] = (dp[j] + dp[j - nums[i]]) % MOD;
            }
        }

        LL total = quickMul(2, n);
        for(int i = 0; i < k; i++) {
            total = ((total - dp[i]*2) %MOD + MOD) % MOD;
        }

        return total;

        /*
        遞歸 TC:O(n*k) SC:O(n*k)
        vector<vector<LL>> memo(n, vector<LL>(k, -1));
        function<LL(int i, LL sum)> dfs = [&](int i, LL sum) -> LL {
            if(i < 0) return sum < k;
            if(sum >= k) return 0;
            if(memo[i][sum] != -1) return memo[i][sum];

            return memo[i][sum] = (dfs(i-1,sum) + dfs(i-1, sum + nums[i])) % MOD;
        };

        return (quickMul(2, n) - dfs(n-1, 0)*2 + MOD) % MOD;
        */
    }
};
