class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        /*
        每一天有多少人知道取決於什麼? 取決於前幾天有多少人已經可以開始傳遞並且沒忘記
        n = 1000 
        dp[i] 
        diff[i]
        */
        vector<ll> dp(n + 1);
        vector<ll> diff(n + 1);
        dp[1] = 1;
        if (1 + delay <= n) diff[delay + 1] += 1;
        if (1 + forget <= n) diff[forget + 1] -= 1;
        ll sum = 0;
        for (int i = 2; i <= n; i++) {
            sum += diff[i];
            dp[i] = (sum + MOD) % MOD;
            if (i + delay <= n) diff[i + delay] = (diff[i + delay] + dp[i]) % MOD;
            if (i + forget <= n) diff[i + forget] = (diff[i + forget] - dp[i]) % MOD;
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            if (i + forget > n) ans = (ans + dp[i]) % MOD;
        }
        return ans;
    }
};