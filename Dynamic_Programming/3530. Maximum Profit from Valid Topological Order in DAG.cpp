// TC:O(n * 2 ^ n) SC:O(2 ^ n)
class Solution {
public:
    long long maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> pre(n, 0);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            pre[v] |= (1 << u);
        }
        int N = 1 << n;
        vector<long long> dp(N, LLONG_MIN / 2);
        dp[0] = 0;
        for (int mask = 0; mask < N; mask++) { // 2^22 * 22
            if (dp[mask] == LLONG_MIN / 2) continue;
            int k = __builtin_popcount(mask); // 之前已經用了多少個？
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i)) && ( (mask & pre[i]) == pre[i] )) {
                    int nxt = mask | (1 << i);
                    long long profit = dp[mask] + (long long)score[i] * (k + 1);
                    dp[nxt] = max(dp[nxt], profit);
                }
            }
        }
        return dp[N - 1];
    }
};
