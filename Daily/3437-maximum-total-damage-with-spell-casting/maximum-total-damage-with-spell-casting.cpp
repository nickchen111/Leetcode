class Solution {
    using ll = long long;
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<ll, ll> cnt;
        for  (auto &p : power) cnt[p] += 1;
        vector<ll> nums;
        for (auto &[k, v] : cnt) nums.emplace_back(k);
        ranges::sort(nums);
        int n = nums.size();
        vector<ll> memo(n, -1);

        auto dfs = [&](this auto&& dfs, int i) -> ll {
            if (i < 0) return 0;
            ll &ret = memo[i];
            if (ret != -1) return ret;
            ret = dfs(i - 1); // 不選

            int j = i;
            while (j && nums[j - 1] >= nums[i] - 2) j -= 1;
            ret = max(ret, dfs(j - 1) + cnt[nums[i]] * nums[i]);
            return ret;
        };

        return dfs(n - 1);
    }
};