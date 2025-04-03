// TC:O(n ^ 4 * k) SC:O(n ^ 3 * k)
class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    int sumOfPowers(vector<int>& nums, int k) {
        int n = nums.size();
        ll mx = *max_element(nums.begin(), nums.end());
        ll mn = *min_element(nums.begin(), nums.end());
        ranges::sort(nums);
        //遞推 但是我的思路是採取枚舉選哪個
        vector dp(n, vector<unordered_map<ll, ll>>(k+1)); // 走到i的時候選了k個會有的diff 以及他的數量
        dp[0][1][mx-mn+1] = 1;
        ll ans = 0;
        for (int i = 1; i < n; i++) {
            dp[i][1][mx-mn+1] = 1; // i 是一定要選的
            //當下要選的數量可能性
            for (int j = 2; j <= min(i+1, k); j++) {
                for(int t = i - 1; t >= 0 && t + 2 >= j; t--) {
                    ll cur_min = LLONG_MAX;
                    for (auto &[mnn, cnt] : dp[t][j-1]) {
                        cur_min = min(mnn, (ll) nums[i] - nums[t]);
                        dp[i][j][cur_min] += cnt;
                    }
                }
            }
            for(auto &[mnn, cnt] : dp[i][k]) {
                ans = (ans + (mnn * (cnt % MOD))) % MOD;
            }
        }
        return ans;
        /*
        枚舉選哪個遞推
        ll initial = mx - mn + 1;
        vector<vector<unordered_map<ll, ll>>> memo(n, vector<unordered_map<ll, ll>>(k+1));
        for (int i = 0; i < n; i++) {
            memo[i][1][initial] = 1;
        }
        auto dfs = [&](auto &&dfs, int i, int j) -> unordered_map<ll, ll> {
            if (j == 1) return memo[i][1];
            if (!memo[i][j].empty()) return memo[i][j];
            
            unordered_map<ll, ll> cur;
            for (int t = i-1; t >= 0 && t + 2 >= j; t--) {
                auto prev = dfs(dfs, t, j - 1);
                for (auto &p : prev) {
                    ll prev_min = p.first;
                    ll count = p.second;
                    ll new_diff = min(prev_min, (ll)nums[i] - nums[t]);
                    cur[new_diff] = (cur[new_diff] + count) % MOD;
                }
            }
            return memo[i][j] = cur;
        };
        
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            auto mp = dfs(dfs, i, k);
            for (auto &p : mp) {
                ans = (ans + (p.first % MOD) * p.second) % MOD;
            }
        }
        return ans;
        */
        /*
        選or不選 遞歸
        vector<vector<unordered_map<ll, ll>>> memo(n, vector<unordered_map<ll, ll>>(k+1));
        auto dfs = [&](auto &&dfs, int i, int j, ll prev, ll min_diff) -> ll {
            if (j > i + 1) return 0;
            if (j == 0) return min_diff;
            ll mask = (prev << 32 | min_diff);
            if (memo[i][j].count(mask)) return memo[i][j][mask];
            ll ans1 = dfs(dfs, i-1, j, prev, min_diff);
            ll ans2 = dfs(dfs, i-1, j-1, nums[i], min(min_diff, (ll)prev - nums[i]));
            return memo[i][j][mask] = (ans1 + ans2) % MOD;
        };
        return dfs(dfs, n - 1, k, LLONG_MAX/2, mx - mn + 1) % MOD;
        */
    }
};
