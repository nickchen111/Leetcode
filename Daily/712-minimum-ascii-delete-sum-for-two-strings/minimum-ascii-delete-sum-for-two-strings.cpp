class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector memo(m, vector<int>(n, INT_MAX));
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                int cur = 0;
                for (int idx = 0; idx <= i; idx++) cur += s1[idx];
                for (int idx = 0; idx <= j; idx++) cur += s2[idx];
                return cur;
            }
            if (memo[i][j] != INT_MAX) return memo[i][j];
            int &ans = memo[i][j];
            if (s1[i] == s2[j]) {
                ans = min(ans, dfs(i - 1, j - 1));
                return ans;
            }

            ans = min(ans,
                      min(dfs(i - 1, j) + s1[i],
                          dfs(i, j - 1) + s2[j]));
            return ans;
        };

        return dfs(m - 1, n - 1);
    }
};
