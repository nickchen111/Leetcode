// TC:O(n) SC:O(n)
class Solution {
    using ll = long long;
public:
    long long countStableSubarrays(vector<int>& cap) {
        // tot - x = 3 * cap[i] 長度至少3
        int n = cap.size();
        unordered_map<int, unordered_map<ll, ll>> mp; // 某個數字 -> 累積和為多少? 總數是?
        ll tot = 0;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            tot += cap[i];
            if (i - 2 >= 0) mp[cap[i-2]][tot - cap[i] - cap[i - 1] - cap[i - 2]] += 1;
            if (mp.count(cap[i])) {
                ans += mp[cap[i]][tot - 3 * (ll)cap[i]];
            }
        }
        return ans;
    }
};
