// TC:O(mlogm + nlogm) SC:O(1)
class Solution {
    using ll = long long;
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        ranges::sort(potions);
        int n = spells.size(), m = potions.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ll target = (success - 1) / spells[i] + 1;
            int j = lower_bound(potions.begin(), potions.end(), target) - potions.begin();
            ans[i] = m - j;
        }
        return ans;
    }
};
