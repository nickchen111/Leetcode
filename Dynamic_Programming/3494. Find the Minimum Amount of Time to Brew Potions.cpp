// TC:O(m * n) SC:O(n)
class Solution {
    using ll = long long;
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size(), m = mana.size();
        vector<ll> dp(n, 0);
        for(int i = 0; i < m; i++) { 
            ll mx = 0; 
            vector<ll> pre(n);
            for(int j = 1; j < n; j++) {
                pre[j] = pre[j-1] + (ll) skill[j-1] * mana[i]; 
                mx = max(mx, dp[j] - pre[j]);
            }
            mx = max(mx, dp[0]);
            dp[0] = mx + (ll) skill[0] * mana[i];
            for(int j = 1 ; j < n; j++) {
                dp[j] = dp[j-1] + (ll) skill[j] * mana[i];
            }
        }
        return dp[n-1];
    }
};
