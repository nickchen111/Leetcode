// TC:O(n) SC:O(n)
using LL = long long;
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        LL ans = LLONG_MAX/2;
        vector<LL> presum1(n+1);
        vector<LL> presum2(n+1);
        for(int i = 0; i < n; i++) {
            presum1[i+1] = presum1[i] + (LL)grid[0][i];
            presum2[i+1] = presum2[i] + (LL)grid[1][i];
        }
        for(int i = 1; i <= n; i++) {
            ans = min(ans, max(presum2[i-1], presum1.back() - presum1[i]));
        }

        return ans;
    }
};
