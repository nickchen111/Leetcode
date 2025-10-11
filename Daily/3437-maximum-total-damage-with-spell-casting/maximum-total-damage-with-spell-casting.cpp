class Solution {
    using ll = long long;
public:
    long long maximumTotalDamage(vector<int>& power) {
        map<ll, ll> cnt;
        for (auto &p : power) cnt[p] += 1;
        set<ll> st(power.begin(), power.end());
        vector<ll> nums(st.begin(), st.end());

        map<ll, ll> mp; // 走到某個數值的時候他的最大值
        mp[-2] = 0;
        ll mx = 0;
        for (int i = 0; i < nums.size(); i++) {
            auto iter = mp.lower_bound(nums[i] - 2);
            iter = prev(iter);
            mp[nums[i]] = max(mx, iter->second + nums[i] * cnt[nums[i]]);
            mx = max(mx, mp[nums[i]]);
        }
        return mx;
    }
};