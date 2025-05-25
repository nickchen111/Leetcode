// TC:O(1) SC:O(1)
class Solution {
    using ll = long long;
public:
    long long minCuttingCost(int n, int m, int k) {
        ll ans = 0;
        if (m > k) {
            ans += (ll) k * (m - k);
        }
        if (n > k) {
            ans += (ll) k * (n - k);
        }
        return ans;
    }
};
