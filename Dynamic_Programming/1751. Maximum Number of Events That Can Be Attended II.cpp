// TC:O(n * k + n * lgn) SC:O(n * k)
class Solution {
    using ll = long long;
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        auto cmp = [&](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        };
        ranges::sort(events, cmp);
        vector dp(n+1, vector<ll>(k+1));
        for(int i = 0; i < n; i++) {
            int start = events[i][0], end = events[i][1], val = events[i][2];
            int t = lower_bound(events.begin(), events.begin() + i, start, [](const vector<int>& e, int s) {
                return e[1] < s;
            }) - events.begin();
            for(int j = 0; j < k; j++) {
                dp[i+1][j+1] = max(dp[i][j+1], dp[t][j] + val);
            }
        }
        return dp[n][k];
    }
};
