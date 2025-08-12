class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numberOfWays(int n, int x) {
        auto quickMul = [&](LL a, LL b) -> LL {
            LL ans = 1;
            while(b) {
                if(b & 1) ans = (ans * a) % MOD;
                a = (a*a) % MOD;
                b >>= 1;
            }

            return ans;
        };

        vector<vector<LL>> memo(n+1, vector<LL>(n, -1));
        function<LL(int i, int sum)> dfs = [&](int i, int sum) -> LL {
            if(sum == n) return 1;
            if(sum > n) return 0;
            if(i > n) return 0;
            if(memo[i][sum] != -1) return memo[i][sum];
            return memo[i][sum] = (dfs(i+1, sum) + dfs(i+1, sum + quickMul(i,x))) % MOD;
        };

        return dfs(1, 0);
    }
};