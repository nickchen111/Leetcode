class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int ans = INT_MIN;
        int n = energy.size();
        vector<vector<int>> pre(k);
        for (int i = 0; i < n; i++) {
            pre[i % k].emplace_back(pre[i % k].size() == 0 ? energy[i] : pre[i % k].back() + energy[i]);
        }

        for (int i = 0; i < k; i++) {
            // 去找出每一列中的最小數值
            int mn = INT_MAX;
            for (int j = 0; j < pre[i % k].size() - 1; j ++) {
                mn = min(mn, pre[i % k][j]);
            }
            
            if (mn != INT_MAX) ans = max({ans, pre[i % k].back() - mn, pre[i % k].back()});
            else ans = max(ans, pre[i % k].back());
        }

        return ans;
    }
};