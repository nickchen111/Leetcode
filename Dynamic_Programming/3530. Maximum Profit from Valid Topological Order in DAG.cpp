// TC:O(n * 2 ^ n) SC:O(2 ^ n)
class Solution {
    using ll = long long;
public:
    long long maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> pre(n, 0);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            pre[v] |= (1 << u);
        }
        int N = 1 << n;
        vector<ll> dp(N, LLONG_MIN/2);
        dp[0] = 0;
        for (int mask = 0; mask < N; mask++) {
            if (dp[mask] == LLONG_MIN/2) continue; // 沒辦法到達的條件
            int k = __builtin_popcount(mask);
            for (int i = 0; i < n; i++) {
                if(!((mask >> i) & 1) && (pre[i] & mask) == pre[i]) {
                    dp[mask | (1 << i)] = max(dp[mask | (1 << i)], dp[mask] + (ll) score[i] * (k + 1));
                } 
            }
        }
        
        return dp[N-1];
    }
};
