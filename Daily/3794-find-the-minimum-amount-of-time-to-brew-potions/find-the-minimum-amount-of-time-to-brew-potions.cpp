class Solution {
    using ll = long long;
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size(), m = mana.size();
        /*
        每個人做的時候都是參考這輪最後那人的結束時間 - 他做的時間 以及自己上一輪結束時間取最大
        */
        vector<ll> dp(n);
        dp[0] = (ll) skill[0] * mana[0];
        for (int i = 1; i < n; i++) {
            dp[i] = dp[i-1] + (ll) skill[i] * mana[0];
        }

        for (int i = 1; i < m; i++) {
            // 先去把上一輪的結果array 取出來然後找出最大值
            ll mx = 0;
            ll pre = 0;
            for (int j = 0; j < n; j++) {
                pre = pre + (j - 1 >= 0 ? (ll) skill[j - 1] * mana[i] : 0);
                mx = max(mx, dp[j] - pre);
            }
            // 這裡開始填到底可以多大
            dp[0] = mx + skill[0] * mana[i];
            for (int j = 1; j < n; j++) {
                dp[j] = dp[j - 1] + (ll) skill[j] * mana[i];
            }
        }

        return dp[n - 1];
    }
};