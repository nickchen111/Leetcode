// TC:O(n) SC:O(1)
class Solution {
    using ll = long long;
public:
    long long maximumProduct(vector<int>& nums, int m) {
        int n = nums.size();
        // 另一種更好的寫法
        ll mn = nums[0], mx = nums[0];
        ll ans = LLONG_MIN;
        for (int i = m - 1; i < n; i++) {
            mn = min(mn, (ll)nums[i - m + 1]);
            mx = max(mx, (ll)nums[i - m + 1]);
            ans = max({ans, mx * nums[i], mn * nums[i]});
        }
        return ans;

        /*
        multiset<ll> set;
        for (int i = n - 1; i >= m - 1; i--) {
            set.insert(nums[i]);
        }
        ll ans = LLONG_MIN;
        for (int i = 0; i < n - m + 1; i++) {
            if (m == 1) ans = max(ans, (ll) nums[i] * nums[i]);
            if (nums[i] < 0) { // 找小的
                ans = max(ans, (ll)nums[i] * *set.begin());
            }
            else {
                ans = max(ans, (ll)nums[i] * *(--set.end()));
            }
            set.erase(set.find(nums[i + m - 1]));
        }
        return ans;
        */
    }
};
